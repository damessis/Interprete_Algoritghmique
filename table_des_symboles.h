
typedef struct
{
  char nom[15];
  float valeur;
} identificateur;

void afficher_identificateur(identificateur idf);
void afficher_table(identificateur* tab, int n);
int rechercher_identificateur(identificateur* tab, char* idf, int n);
float valeur_idf(identificateur* tab, char* nom, int n);
