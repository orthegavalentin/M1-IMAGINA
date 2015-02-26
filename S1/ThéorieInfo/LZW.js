var LZW = {
    compress: function (uncompressed) {
        "use strict";
		
        var i,
            dico = {},
            c,
            wc,
            w = "",
            result = [],
            dicoSize = 256;
		//On remplit le dictionnaires des 256 caractères ASCII
        for (i = 0; i < 256; i += 1) {
            dico[String.fromCharCode(i)] = i;
        }
 		
		
        for (i = 0; i < uncompressed.length; i += 1) {			//on lit un caractere apres l'autre de la variable uncompressed
            c = uncompressed.charAt(i);
            wc = w + c;
			
            if (dico.hasOwnProperty(wc)) {						//si w+c existe dans le dictionnaire
                w = wc;											// alors w=w+c
            } else {											//sinon
                dico[wc] = dicoSize++;							// on ajoute w + c au dico...
                result.push(dico[w]);							// on écrit le code de w
                w = String(c);									// w = c
            }
        }
		
        if (w !== "") {
            result.push(dico[w]);								//on ajoute le code de w dans la variable de sortie
        }
        return result;
    },
 
 
    decompress: function (compressed) {
        "use strict";
        var i,
            dico = [],
            w,
            result,
            k,
            entry = "",
            dicoSize = 256;
		
        for (i = 0; i < 256; i += 1) {
            dico[i] = String.fromCharCode(i);
        }
 
        w = String.fromCharCode(compressed[0]);					//lecture du premier caractère
        result = w;												//on ajoute ce caractère dans la sortie
        for (i = 1; i < compressed.length; i += 1) {			//On lit un caractere apres l'autre de la variable compressed
            k = compressed[i];
            if (dico[k]) {
                entry = dico[k];
            } else {
                if (k === dicoSize) {
                    entry = w + w.charAt(0);
                } else {
                    return null;
                }
            }
 
            result += entry;
			
            dico[dicoSize++] = w + entry.charAt(0);
 
            w = entry;
        }
        return result;
    }
};