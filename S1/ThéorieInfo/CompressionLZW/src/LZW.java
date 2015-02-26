import java.util.*;
 
public class LZW {
    //Algo de compression
    public static List<Integer> compression(String uncompressed) {
    	
        int dicoTaille = 256;
        Map<String,Integer> dictionnaire = new HashMap<String,Integer>();
        for (int i = 0; i < 256; i++){
        	dictionnaire.put("" + (char)i, i);
        }
        
        String w = "";
        
        List<Integer> resultat = new ArrayList<Integer>();
        for (char c : uncompressed.toCharArray()) {
            String wc = w + c;
            if (dictionnaire.containsKey(wc))
                w = wc;
            else {
            	resultat.add(dictionnaire.get(w));
                // Add wc to the dictionary.
                dictionnaire.put(wc, dicoTaille++);
                w = "" + c;
            }
        }
 
        // Output the code for w.
        if (!w.equals(""))
        	resultat.add(dictionnaire.get(w));
        return resultat;
    }
 
    //Algo de décompression
    public static String decompression(List<Integer> compressed) {
    	
        int dicoTaille = 256;
        Map<Integer,String> dictionnaire = new HashMap<Integer,String>();
        for (int i = 0; i < 256; i++)
        	dictionnaire.put(i, "" + (char)i);
 
        String w = "" + (char)(int)compressed.remove(0);
        StringBuffer resultat = new StringBuffer(w);
        for (int k : compressed) {
            String entry;
            if (dictionnaire.containsKey(k))
                entry = dictionnaire.get(k);
            else if (k == dicoTaille)
                entry = w + w.charAt(0);
            else
                throw new IllegalArgumentException("Mauvaise compression à : " + k);
 
            resultat.append(entry);
 
            // Add w+entry[0] to the dictionary.
            dictionnaire.put(dicoTaille++, w + entry.charAt(0));
 
            w = entry;
        }
        return resultat.toString();
    }
 
    public static void main(String[] args) {
        List<Integer> compressed = compression("Hello World nice to meet you");
        System.out.println(compressed);
        String decompressed = decompression(compressed);
        System.out.println(decompressed);
    }
}