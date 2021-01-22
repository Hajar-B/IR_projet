# Prérequis :
>> sudo apt install python3-pip

>> pip3 install matplotlib

>> pip3 install folium

# Exécution des scripts:
## Commandes :
>> gcc graphe -o analyzer.c monumentReader.c mainMonument.c 

>> ./graphe

>> python3 visualisation.py

## Visualisation de la carte
- double click sur le fichier 'via.html'
- une page web s'ouvrira sur votre navigateur

Pour visualiser les itinéraires des autres algorithmes (même s'ils sont tous identiques):
- ouvrir mainMonument.c
- ligne 92: remplacer le paramètre de la fonction saveGraph (g pour Kruskal, g2 pour Boruvka, g3 pour Prim, g4 pour la nouvelle solution)


