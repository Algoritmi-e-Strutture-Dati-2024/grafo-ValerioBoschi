#include <iostream>
#define MAX_NODI 100
#define INF 1000000000 // Rappresenta l'assenza di connessione

template <typename T>
class Grafo {
private:
    T nodi[MAX_NODI]; // Array dei nodi
    int matriceAdiacenza[MAX_NODI][MAX_NODI]; // Matrice di adiacenza
    bool esisteNodo[MAX_NODI]; // Indica se un nodo esiste
    int numeroNodi = 0; // Numero attuale di nodi

public:
    // Costruttore
    Grafo() {
        for (int i = 0; i < MAX_NODI; ++i) {
            esisteNodo[i] = false;
            for (int j = 0; j < MAX_NODI; ++j) {
                matriceAdiacenza[i][j] = INF;
            }
            matriceAdiacenza[i][i] = 0; // La distanza da un nodo a se stesso è 0
        }
    }
// Trova l'arco con peso minimo tra gli archi uscenti di un nodo dato
void arcoMinimo(const T& nodo) const {
    int indice = trovaIndice(nodo);
    if (indice == -1) {
        std::cout << "Errore: il nodo non esiste.\n";
        return;
    }

    int pesoMinimo = INF;
    int nodoDestinazione = -1;

    for (int i = 0; i < numeroNodi; ++i) {
        if (esisteNodo[i] && matriceAdiacenza[indice][i] < pesoMinimo) {
            pesoMinimo = matriceAdiacenza[indice][i];
            nodoDestinazione = i;
        }
    }

    if (nodoDestinazione != -1) {
        std::cout << "L'arco con peso minimo uscendo da " << nodo << " è verso " 
                  << nodi[nodoDestinazione] << " con peso " << pesoMinimo << ".\n";
    } else {
        std::cout << "Il nodo " << nodo << " non ha archi uscenti.\n";
    }
}
    // Aggiunge un nodo al grafo, in input viene inserito il valore che rappresenta quel nodo (es. nome della cittá)
    void aggiungiNodo(const T& nodo) {
        if (numeroNodi >= MAX_NODI) {
            std::cout << "Errore: numero massimo di nodi raggiunto.\n";
            return;
        }
        for (int i = 0; i < numeroNodi; ++i) {
            if (esisteNodo[i] && nodi[i] == nodo) {
                std::cout << "Errore: il nodo esiste già.\n";
                return;
            }
        }
        nodi[numeroNodi] = nodo;
        esisteNodo[numeroNodi] = true;
        numeroNodi++;
    }

    // Aggiunge un arco tra due nodi dando in input i nomi dei nodi e il peso del loro arco
    void aggiungiArco(const T& sorgente, const T& destinazione, int peso) {
        int indiceSorgente = trovaIndice(sorgente);
        int indiceDestinazione = trovaIndice(destinazione);

        if (indiceSorgente == -1 || indiceDestinazione == -1) {
            std::cout << "Errore: uno o entrambi i nodi non esistono.\n";
            return;
        }
        matriceAdiacenza[indiceSorgente][indiceDestinazione] = peso;
    }

    // Rimuove un nodo dando in input il nome del nodo
    void rimuoviNodo(const T& nodo) {
        int indice = trovaIndice(nodo);
        if (indice == -1) {
            std::cout << "Errore: il nodo non esiste.\n";
            return;
        }
        esisteNodo[indice] = false;
        for (int i = 0; i < MAX_NODI; ++i) {
            matriceAdiacenza[indice][i] = INF;
            matriceAdiacenza[i][indice] = INF;
        }
    }

    // Rimuove un arco tra due nodi dando in input il nome del nodo di partenza e del nodo di arrivo
    void rimuoviArco(const T& sorgente, const T& destinazione) {
        int indiceSorgente = trovaIndice(sorgente);
        int indiceDestinazione = trovaIndice(destinazione);

        if (indiceSorgente == -1 || indiceDestinazione == -1) {
            std::cout << "Errore: uno o entrambi i nodi non esistono.\n";
            return;
        }
        matriceAdiacenza[indiceSorgente][indiceDestinazione] = INF;
    }

    // Restituisce i nodi adiacenti a un dato nodo
    void nodiAdiacenti(const T& nodo) const {
        int indice = trovaIndice(nodo);
        if (indice == -1) {
            std::cout << "Errore: il nodo non esiste.\n";
            return;
        }
        std::cout << "Nodi adiacenti a " << nodo << ": ";
        for (int i = 0; i < numeroNodi; ++i) {
            if (esisteNodo[i] && matriceAdiacenza[indice][i] != INF) {
                std::cout << nodi[i] << " (peso: " << matriceAdiacenza[indice][i] << ") ";
            }
        }
        std::cout << "\n";
    }

    // Stampa la matrice di adiacenza
    void stampa() const {
        std::cout << "Matrice di Adiacenza:\n";
        for (int i = 0; i < numeroNodi; ++i) {
            if (!esisteNodo[i]) continue;

            for (int j = 0; j < numeroNodi; ++j) {
                if (!esisteNodo[j]) continue;

                if (matriceAdiacenza[i][j] == INF) {
                    std::cout << "INF ";
                } else {
                    std::cout << matriceAdiacenza[i][j] << " ";
                }
            }
            std::cout << "\n";
        }
    }

    // Verifica se un nodo esiste
    bool verificaNodo(const T& nodo) const {
        return trovaIndice(nodo) != -1;
    }

    // Verifica se un arco esiste
    bool verificaArco(const T& sorgente, const T& destinazione) const {
        int indiceSorgente = trovaIndice(sorgente);
        int indiceDestinazione = trovaIndice(destinazione);

        if (indiceSorgente == -1 || indiceDestinazione == -1) {
            return false;
        }
        return matriceAdiacenza[indiceSorgente][indiceDestinazione] != INF;
    }
    
private:
    // Trova l'indice di un nodo
    int trovaIndice(const T& nodo) const {
        for (int i = 0; i < numeroNodi; ++i) {
            if (esisteNodo[i] && nodi[i] == nodo) {
                return i;
            }
        }
        return -1;
    }
};
