#include <iostream>
#include "Grafo.h" // Inclusione della classe

int main() {
    // Creazione del grafo
    Grafo<std::string> grafo;

    // Aggiunta dei nodi
    grafo.aggiungiNodo("Dybala");
    grafo.aggiungiNodo("Lukaku");
    grafo.aggiungiNodo("Osimhen");
    grafo.aggiungiNodo("Lautaro");
    grafo.aggiungiNodo("Kvaratskhelia");

   //il peso degli archi é dato dalla partite giocate insieme dai calciatori.

    // Aggiunta degli archi
    grafo.aggiungiArco("Dybala", "Lukaku", 10);
    grafo.aggiungiArco("Dybala", "Lautaro", 5);
    grafo.aggiungiArco("Lukaku", "Lautaro", 20);
    grafo.aggiungiArco("Osimhen", "Kvaratskhelia", 15);
    grafo.aggiungiArco("Dybala", "Osimhen", 8);
    grafo.aggiungiArco("Lautaro", "Kvaratskhelia", 12);

    // Visualizzazione del grafo
    grafo.stampa();

    // Ricerca e manipolazione
    std::cout << "\nVerifica se il nodo 'Dybala' esiste: " << (grafo.verificaNodo("Dybala") ? "Sì" : "No") << "\n";
    std::cout << "Verifica se esiste un arco tra 'Dybala' e 'Lukaku': " << (grafo.verificaArco("Dybala", "Lukaku") ? "Sì" : "No") << "\n";

    std::cout << "\nNodi adiacenti a 'Dybala':\n";
    grafo.nodiAdiacenti("Dybala");

    // Rimozione di un arco
    std::cout << "\nRimuovo l'arco tra 'Dybala' e 'Lukaku'.\n";
    grafo.rimuoviArco("Dybala", "Lukaku");
    grafo.stampa();

    // Rimozione di un nodo
    std::cout << "\nRimuovo il nodo 'Osimhen' e tutti i suoi archi.\n";
    grafo.rimuoviNodo("Osimhen");
    grafo.stampa();

    // Aggiunta di nuovi nodi e archi
    std::cout << "\nAggiungo un nuovo nodo 'Zaniolo' e un arco con 'Dybala'.\n";
    grafo.aggiungiNodo("Zaniolo");
    grafo.aggiungiArco("Dybala", "Zaniolo", 6);
    grafo.stampa();

    // Verifica se due nodi sono connessi    
    std::string nodo1 = "Dybala";  
     std::string nodo2 = "Lukaku"; 
     if (grafo.verificaArco(nodo1, nodo2)) {        std::cout << "I nodi " << nodo1 << " e " << nodo2 << " sono connessi.\n";    } 
          else {        std::cout << "I nodi " << nodo1 << " e " << nodo2 << " NON sono connessi.\n";    }  
    nodo1 = "Dybala";    nodo2 = "Kvaratskhelia";  
if (grafo.verificaArco(nodo1, nodo2)) {std::cout << "I nodi " << nodo1 << " e " << nodo2 << " sono connessi.\n";    } 
else {        std::cout << "I nodi " << nodo1 << " e " << nodo2 << " NON sono connessi.\n"};   

 std:: cout << "\n trova arco con peso minimo uscendo da 'Dybala':\n ";
   grafo.arcoMinimo("Dybala");
    return 0;
}

#define MAX_NODI 100
#define INF 999999
// Funzione per trovare il nodo con la distanza minima tra quelli non ancora visitati
int trovaMinimo(int distanze[], bool visitati[], int numeroNodi) {
    int min = INF;
    int indiceMinimo = -1;

    for (int i = 0; i < numeroNodi; i++) {
        if (!visitati[i] && distanze[i] < min) {
            min = distanze[i];
            indiceMinimo = i;
        }
    }

    return indiceMinimo;
}

// Algoritmo di Dijkstra
void dijkstra(int grafo[MAX_NODI][MAX_NODI], int numeroNodi, int sorgente) {
    int distanze[MAX_NODI];      // Array per le distanze minime
    bool visitati[MAX_NODI];    // Array per tenere traccia dei nodi visitati
    int predecessori[MAX_NODI]; // Array per ricostruire i percorsi

    // Inizializza distanze, visitati e predecessori
    for (int i = 0; i < numeroNodi; i++) {
        distanze[i] = INF;
        visitati[i] = false;
        predecessori[i] = -1;
    }

    distanze[sorgente] = 0; // La distanza del nodo sorgente da se stesso è 0

    for (int i = 0; i < numeroNodi - 1; i++) {
        // Trova il nodo con la distanza minima
        int nodoCorrente = trovaMinimo(distanze, visitati, numeroNodi);

        if (nodoCorrente == -1) {
            break; // Non ci sono più nodi raggiungibili
        }

        visitati[nodoCorrente] = true;

        // Aggiorna le distanze dei nodi adiacenti
        for (int j = 0; j < numeroNodi; j++) {
            if (grafo[nodoCorrente][j] != INF && !visitati[j]) {
                int nuovaDistanza = distanze[nodoCorrente] + grafo[nodoCorrente][j];
                if (nuovaDistanza < distanze[j]) {
                    distanze[j] = nuovaDistanza;
                    predecessori[j] = nodoCorrente;
                }
            }
        }
    }

    // Stampa i risultati
    std::cout << "Distanze dal nodo " << sorgente << ":\n";
    for (int i = 0; i < numeroNodi; i++) {
        if (distanze[i] == INF) {
            std::cout << "Nodo " << i << ": INF\n";
        } else {
            std::cout << "Nodo " << i << ": " << distanze[i] << "\n";
        }
    }
}
