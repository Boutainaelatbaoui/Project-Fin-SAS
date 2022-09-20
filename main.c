#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


typedef struct{
    int code;
    char nom[25];
    int quantite;
    float prix;
    float prixttc;
    int jour, mois, annee;
}Produit;

float maxPrixttc = 0;
float minPrixttc = 0;

Produit productTable[200];
Produit productVendu[200];
int nbrProduct = 0;
int nbrProductVendu = 0;
int nbrProductVenduJour = 0;

void afficherMenu();
void ajouterProduit();
void ajouterPlusProduit();
void afficherProduit();
void listerOrdreAlphabetique();
void listerOrdrePrix();
void acheterProduit();
void rechercherParCode();
void rechercherParQuantite();
void etatStock();
void alimenterStock();
void supprimerParCode();
void statistiqueVente();
void quitterApp();


int main(){
    int choix;
    while(1){
        afficherMenu();
        printf("Veuillez entrer votre choix: ");
        scanf("%d", &choix);
        fflush(stdin);
        printf("======================================================================================\n");
        switch(choix){
            case 1:

                ajouterProduit();
                printf("\nVotre produit est ajoute avec succes.\n");
                break;
            case 2:

                ajouterPlusProduit();
                printf("\nVos produits sont ajoutes avec succes.\n");
                break;
            case 3:
                if(nbrProduct != 0){
                    printf("\n---------------La liste de vos produits---------------\n");
                    afficherProduit();
                }
                else{
                    printf("Il n y a pas des produits!!\n");
                }
                break;
            case 4:
                if(nbrProduct != 0){
                    printf("\n---------------La liste de vos produits Lister selon l'ordre decroissant du prix---------------\n");
                    listerOrdrePrix();
                }
                else{
                    printf("Il n y a pas des produits!!\n");
                }
                break;
            case 5:
                if(nbrProduct != 0){
                    printf("\n---------------La liste de vos produits Lister selon l'ordre alphabetique croissant du nom---------------\n");
                    listerOrdreAlphabetique();
                }
                else{
                    printf("Il n y a pas des produits!!\n");
                }
                break;
            case 6:
                acheterProduit();
                break;
            case 7:
                rechercherParCode();
                break;
            case 8:
                rechercherParQuantite();
                break;
            case 9:
                etatStock();
                break;
            case 10:
                alimenterStock();
                break;
            case 11:
                supprimerParCode();
                break;
            case 12:
                if(nbrProductVendu != 0){
                    statistiqueVente();
                }
                else{
                    printf("Il n'existe aucun produit dans cette journee!!\n");
                }
                break;
            case 13:
                quitterApp();
                break;
            default:
                printf("Choix invalide!!\nVeuillez entrer un choix entre 1 et 12\n");
                break;
        }
    }
    return 0;
}

void afficherMenu(){
    printf("\n\t\t\t\tBienvenue dans notre application de gestion de pharmacie\t\t\t\t\n");
    printf("\nVeuillez choisir a partir de ce Menu:\n");
    printf("===================================================================================\n");
    printf("1.  Ajouter un nouveau produit\n");
    printf("2.  Ajouter plusieurs nouveaux produits\n");
    printf("3.  Afficher les produits\n");
    printf("4.  Lister tous les produits selon l'ordre alphabetique croissant du nom\n");
    printf("5.  Lister tous les produits selon l'ordre decroissant du prix\n");
    printf("6.  Acheter produit\n");
    printf("7.  Rechercher les produits par code\n");
    printf("8.  Rechercher les produits Par quantite\n");
    printf("9.  Etat du stock: permet d'afficher les produits dont la quantite est inferieure a 3\n");
    printf("10. Alimenter le stock\n");
    printf("11. Supprimer les produits par code\n");
    printf("12. Statistique de vente\n");
    printf("13. Quitter l'application\n");
    printf("======================================================================================\n");
}

void ajouterProduit(){

    printf("Veuillez entrer le code produit: ");
    scanf("%d", &productTable[nbrProduct].code);
    printf("\nVeuillez entrer le nom de produit: ");
    scanf("%s", productTable[nbrProduct].nom);
    printf("\nVeuillez entrer la quantite de produit: ");
    scanf("%d", &productTable[nbrProduct].quantite);
    printf("\nVeuillez entrer le prix de produit: ");
    scanf("%f", &productTable[nbrProduct].prix);
    productTable[nbrProduct].prixttc = productTable[nbrProduct].prix + (productTable[nbrProduct].prix * 0.15);
    nbrProduct++;
}

void ajouterPlusProduit(){
    int nbr, i;

    printf("Veuillez entrer le nombre de produit: ");
    scanf("%d", &nbr);
    for(i=0; i<nbr; i++){
        printf("\n-----------------------------------------\n");
        ajouterProduit();
    }
}

void afficherProduit(){
    int i;
    for(i=0; i<nbrProduct; i++){
        printf("\n---------------les donnees de produit N-%d---------------\n", i+1);
        printf("Le code produit :           %d\n", productTable[i].code);
        printf("Le nom de produit :         %s\n", productTable[i].nom);
        printf("La quantite de produit :    %d\n", productTable[i].quantite);
        printf("Le prix de produit :        %.2f DH\n", productTable[i].prix);
        printf("Le prix TTC de produit :    %.2f DH\n", productTable[i].prixttc);
        printf("\n-------------------------------------------------------\n");
    }
}

void listerOrdreAlphabetique(){
    int i, j;
    Produit temp;
    for(i=0; i<nbrProduct; i++){
        for(j=i+1; j<nbrProduct; j++){
            if( strcmp(productTable[i].nom, productTable[j].nom) > 0) {
                Produit temp =  productTable[i];
                productTable[i] = productTable[j];
                productTable[j] = temp;
            }
        }
    }
    afficherProduit();
}

void listerOrdrePrix(){
    int i, j;
    Produit temp;
    for(i=0; i<nbrProduct; i++){
        for(j=i+1; j < nbrProduct; j++){
            if(productTable[i].prix < productTable[j].prix){
                temp = productTable[i];
                productTable[i] = productTable[j];
                productTable[j] = temp;
            }
        }
    }
    afficherProduit();
}

void acheterProduit(){
    int compteur = 0;
    int i, code, quantite;
    printf("Veuillez entrer le code produit: ");
    scanf("%d", &code);
    for(i=0; i<nbrProduct; i++){
        if(code == productTable[i].code){
            printf("Veuillez entrer la quantite: ");
            scanf("%d", &quantite);
            if(quantite <= productTable[i].quantite && quantite != 0){
                productTable[i].quantite -= quantite;
                time_t t = time(NULL);
                struct tm tm = *localtime(&t);

                productVendu[i].jour = tm.tm_mday;
                productVendu[i].mois = tm.tm_mon + 1;
                productVendu[i].annee = tm.tm_year + 1900;
                productVendu[i].code = productTable[i].code;
                strcpy(productVendu[i].nom, productTable[i].nom);
                productVendu[i].quantite = productTable[i].quantite;
                productVendu[i].prix = productTable[i].prix * quantite;
                productVendu[i].prixttc = productTable[nbrProduct].prix + (productTable[nbrProduct].prix * 0.15);

                nbrProductVendu++;

                printf("Vous avez achete le produit %s avec un prix TTC de %.2f DH, le %d-%d-%d.\n",
                       productTable[i].nom, productTable[i].prixttc, productVendu[i].jour, productVendu[i].mois, productVendu[i].annee);

            }
            else{
                printf("La quantite est insuffissante!!\n");
            }
            compteur++;
            break;
        }
    }
    if(compteur == 0){
        printf("Produit introuvable!!\n");
    }
}

void rechercherParCode(){
    int i, code;
    printf("Veuillez entrer le code produit: ");
    scanf("%d", &code);
    for(i=0; i<nbrProduct; i++){
        if(productTable[i].code == code){
            printf("Le code produit :           %d\n", productTable[i].code);
            printf("Le nom de produit :         %s\n", productTable[i].nom);
            printf("La quantite de produit :    %d\n", productTable[i].quantite);
            printf("Le prix de produit :        %.2f DH\n", productTable[i].prix);
            printf("Le prix TTC de produit :    %.2f DH\n", productTable[i].prixttc);
            printf("\n-------------------------------------------------------\n");
            break;
        }
        else{
            printf("Produit introuvable!!\n");
        }
    }
}

void rechercherParQuantite(){
    system("cls");
    int i, quantite;
    printf("Veuillez entrer la quantite de produit: ");
    scanf("%d", &quantite);
    for(i=0; i<nbrProduct; i++){
        if(productTable[i].quantite == quantite){
            printf("Le code produit :           %d\n", productTable[i].code);
            printf("Le nom de produit :         %s\n", productTable[i].nom);
            printf("La quantite de produit :    %d\n", productTable[i].quantite);
            printf("Le prix de produit :        %.2f DH\n", productTable[i].prix);
            printf("Le prix TTC de produit :    %.2f DH\n", productTable[i].prixttc);
            printf("\n-------------------------------------------------------\n");
            break;
        }
        else{
            printf("Produit introuvable!!\n");
        }
    }
}

void etatStock(){
    int i;
    for(i=0; i<nbrProduct; i++){
        if(productTable[i].quantite < 3){
            printf("Le code produit :           %d\n", productTable[i].code);
            printf("Le nom de produit :         %s\n", productTable[i].nom);
            printf("La quantite de produit :    %d\n", productTable[i].quantite);
            printf("Le prix de produit :        %.2f DH\n", productTable[i].prix);
            printf("Le prix TTC de produit :    %.2f DH\n", productTable[i].prixttc);
            printf("\n-------------------------------------------------------\n");
            break;
        }
        else{
            printf("Tous les produits sont superieurs de 3.\n");
        }
    }
}

void alimenterStock(){
    int i, code, quantite;
    printf("Entrer le code produit:\n");
    scanf("%d", &code);
    for(i=0; i<nbrProduct; i++){
        if(code == productTable[i].code){
            printf("Entrer la quantite a ajouter: ");
            scanf("%d", &quantite);
            printf("La quantite de produit avec le code %d avant l'ajout est: %d\n", productTable[i].code, productTable[i].quantite);
            productTable[i].quantite += quantite;
            printf("La quantite de produit avec le code %d apres l'ajout est: %d\n", productTable[i].code, productTable[i].quantite);
            break;
        }
        else{
            printf("Produit introuvable\n");
        }
    }
}

void supprimerParCode(){
    int i, j, code;
    Produit temp;
    printf("Veuillez entrer le code produit: ");
    scanf("%d", &code);
    for(i=0; i<nbrProduct; i++){
        if(code == productTable[i].code){
            for(j=i; j<nbrProduct; j++){
                temp = productTable[j];
                productTable[j] = productTable[j+1];
                productTable[j+1] = temp;
            }
            nbrProduct--;
            printf("Le produit avec le code %d est supprime avec succes.\n", productTable[i].code);
        }
        else{
            printf("Produit introuvable!!\n");
        }
    }
}

void statistiqueVente(){
    int i, j;
    float totalPrix = 0;
    float moyennePrix;
    for(i=0; i<nbrProductVendu; i++){
        time_t t = time(NULL);
        struct tm tm = *localtime(&t);
        int jour = tm.tm_mday;
        if(productVendu[i].jour == jour){
            totalPrix += productVendu[i].prix;
            nbrProductVenduJour++;

            if(productVendu[i].prixttc > maxPrixttc){
                maxPrixttc = productVendu[i].prixttc;
            }
            if (productVendu[i].prixttc < minPrixttc || minPrixttc == 0) {
               minPrixttc = productVendu[i].prixttc;
           }
        }
        moyennePrix = totalPrix / nbrProductVenduJour;
    }
    printf("Le total des prix des produits vendus en journee courante est:       %.2f\n", totalPrix);
    printf("La moyenne des prix des produits vendus en journee courante est:     %.2f\n", moyennePrix);
    printf("Le max des prix des produits vendus en journee courante est:         %.2f\n", maxPrixttc);
    printf("Le min des prix des produits vendus en journee courante est:         %.2f\n", minPrixttc);
}

void quitterApp(){
    printf("Au revoir\n");
    exit(0);
}

