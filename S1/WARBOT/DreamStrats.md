# Stratégies WarBot

## Base
- Ping de position à toutes les unités
- Compter les pings des unités
- Garder un nombre ς d'explorateurs en service
- Adapter la production d'unités en fonction de leur nombre actuel et de nombre de ticks écoulés
- *Enclencher le plan Zerg Rush à un moment donné*

## Explorateurs
- Déplacement random
- Perception de bouffe ⇨ envoi du message *BOUFFE!!!* aux explorateurs, soldats, ingénieurs ⇨ Ramasser bouffe
- Réception d'un message *BOUFFE!!!* ⇨ déplacement vers la cible du message
- Détection d'un soldat ennemi ⇨ envoi d'un message *SOLDAT!!!* aux soldats alliés ⇨ faire un demi-tour
- Sac plein ⇨ retour dépôt à la base

## Soldats
- Perception de bouffe ⇨ envoi du message "BOUFFE!!!" aux explorateurs, soldats, ingénieurs
- Détection d'un soldat ennemi ⇨ envoi d'un message *SOLDAT!!!* aux soldats alliés ⇨ mode **attaque**
- Quand la vie descend en dessous d'un certain seuil ⇨ mode **fuite** vers une tourelle ⇨ Récupération sac tourelle
	- Si vie > α% ⇨ retour en mode **libre**
	- Si vie < α% ⇨ **fuite** vers la base
- A la réception d'un message *SOLDAT!!!*
	- Si en mode **libre** ⇨ mouvement vers l'expéditeur du message si la distance est inférieure à β  (mode **chasse**)
	- Si en mode **chasse**
		- Si distance du nouveau message < à la cible actuelle, mouvement vers l'expéditeur
		- Si distance du nouveau message > à la cible actuelle, ignorer
- Distance de sécurité entre ses collègues soldats
- En mode **attaque** faire du hit&run (se déplacer pendant le temps de rechargement)

## Ingénieurs
- Placer 1 (ou 2) tours proche de la base
- A la réception du message *BOUFFE!!!* ⇨ fermer l'écoute ⇨ se diriger vers la source ⇨ déployer une tourelle ⇨ rouvrir l'écoute et attente du prochain message *BOUFFE!!!*.

## Kamikazes
- Stacker un nombre ζ de Kamikazes près de la base ⇨ mode **rush nexus** (contournement des stacks de bouffe ?)

## Bugs
- Si *isBlocked() = true* ⇨ angle de direction +180°.
