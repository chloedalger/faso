Le r�pertoire RENDU contient 2 dossiers ainsi qu'un PDF.

Le PDF est la synth�se de notre projet.

Le dossier borne contient tout le code n�cessaire � faire fonctionner la borne de notre projet :
-Le fichier mainBorne.c contient les fonctions n�cessaires � l'affichage de l'interface.
-Le fichier grovepi.c contient tout ce qu'il faut pour faire fonctionner le shield. 
-Le fichier borneScript.exp permet de faire communiquer la borne et la commande par un appel � scp.
-Le fichier communication.txt est le fichier qui va �tre envoy� � l'autre raspberry pour effectuer la communication.

Le dossier borne contient tout le code n�cessaire � faire fonctionner la commande de notre projet :
-Le fichier mainCommande.c est le fichier qui contient un script lisant le fichier communication.txt et lan�ant le script python pour diriger l'utilisateur.
-Le fichier interfaceSenseHat.py permet d�afficher les fl�ches � l�utilisateur et donc de le diriger vers l'oeuvre.
-Le fichier commandeScript.exp permet de faire communiquer la borne et la commande par un appel � scp.
-Le fichier communication.txt est le fichier qui va �tre envoy� � l'autre raspberry pour effectuer la communication.