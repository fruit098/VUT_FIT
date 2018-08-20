/**
 * Kostra programu pro 3. projekt IZP 2017/18
 *
 * Jednoducha shlukova analyza
 * Unweighted pair-group average
 * https://is.muni.cz/th/172767/fi_b/5739129/web/web/usrov.html
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h>

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);


    c->size = 0;
    c->capacity = cap;
    if (cap == 0 ){
        c -> obj = NULL;
    }
    c -> obj  = (struct obj_t *) malloc(sizeof(struct obj_t ) * cap);
    if (c->obj == NULL ){
        printf("Init of cluster made bad\n");
    }



    // TODO

}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
    c-> size = 0;
    c-> capacity = 0;
    free(c->obj);
    c-> obj = NULL;
    // TODO
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    // TUTO FUNKCI NEMENTE
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
    if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t*)arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{

    // TODO
    int cap = c->capacity;
    int size = c->size;
    if (size < cap) {
        c->obj[size] = obj ;
        c->size += 1;
    } else {
        c = resize_cluster(c, cap + CLUSTER_CHUNK);
        c->obj[c->size] = obj;
        c->size += 1;
    }
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);

    // TODO

    int size_c2 = c2->size;


    size_c2 = size_c2 - 1;

    while (size_c2 >= 0){
        append_cluster(c1, c2->obj[size_c2]);
        size_c2 = size_c2 - 1;
    }

    sort_cluster(c1);

}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);

    // TODO
    if ( narr - 1 == idx) {
        clear_cluster(&(carr[idx]));
        return narr - 1;
    } else {
        clear_cluster(&(carr[idx]));
        for(; idx < narr - 1; idx++ ){
            carr[idx] = carr[idx + 1];

        }

        return narr - 1;
    }
    // poposuvat pointre
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    // TODO
    return hypotf((o1->x) - (o2->x) , (o1->y) - (o2->y));

}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);
    float vzdalenost = 0.0 ;
    // TODO

    // pocita vzialenost pre kazdu kombinaciu parov z 2 clustrov, nasledne to podeli poctom clustrov
    for( int i = 0; i < (c1->size) ; ++i){
        for(int j = 0 ; j < (c2->size); ++j){
            vzdalenost += obj_distance(&(c1->obj[i]),&(c2->obj[j]));
        }
    }

    return vzdalenost/ ((c1->size) * (c2->size));
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);

    // TODO
    // pre vsetky clustre v poli to vypocita vzdialenost a vzdy najmensiu moznu si uklada a tiez aj indexy danych clustrov
    // ktore maju najmensiue vziadlenost
    float najmensia_vzdialenost = cluster_distance(&(carr[0]), &(carr[1]));
    int i1 = 0;
    int i2 = 1;
    for( int i = 0; i < (narr - 1); ++i ){
        for(int j = i + 1; j < (narr); ++j){
            if(najmensia_vzdialenost > cluster_distance(&(carr[i]),&(carr[j]))){
                najmensia_vzdialenost = cluster_distance(&(carr[i]),&(carr[j]));
                i1 = i;
                i2 = j;
            }
        }
    }
    *c1 = i1;
    *c2 = i2;
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c);

void sort_cluster(struct cluster_t *c) {
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE

    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);
    // TODO
    FILE *f;


    char str[6];
    char *count = "count";
    long int objC;

    f = fopen( filename, "r" );
    if(f == NULL){
        return -1;
    }

    if(fscanf(f, "%5s=%ld" , str , &objC ) == 2 ){
        for(int idx = 0 ; idx < 6; ++idx ){
            if(str[idx] != count[idx]){
                fclose(f);
                return -1;
            }
        }
        if (objC <  1 ){
            fclose(f);
            return -1;
        }

    }else{
        fclose(f);
        return -1;
    }

    // cluster arr initiliazing


    *arr = malloc(sizeof(struct cluster_t ) * objC);


    if(arr != NULL ){
    } else {
        arr = NULL;
        return -1;
    }


    //obj reading

    for(int j = 0; j < objC; ++j){
        int objID;
        int X;
        int Y;
        if ((fscanf(f, "%d %d %d " , &objID , &X , &Y ) != 3) || X < 0 || X >= 1000 || Y < 0 || Y >= 1000 || objID < 0){
            // cluster clearin ak sa stala chyba v reade
            if ( j != 0)
            {
                                for(int i = 0; i < j; i++){
                    clear_cluster(&(*arr)[i]);
                }

            }
            fclose(f);
            free(*arr);
            *arr = NULL;
            arr = NULL;
            return -1;
        }
        // inicializacia clustra
        init_cluster(&(*arr)[j],1);

        // init of obj and then add to cluster
        struct obj_t obj = {
                .y = Y,
                .x = X,
                .id = objID
        };

        append_cluster(&(*arr)[j],obj);
    }

    fclose(f);
    return objC;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);

        print_cluster(&(carr[i]));
    }
}

int main(int argc, char *argv[])
{
    struct cluster_t *clusters;


    // defaultny pocet clustrov je jedna
    long int max_clustrov = 1;
    long int pocet_clustrov;

    pocet_clustrov = 0;

    // osetrenie nezvycajnych vstupov
    if (argc > 3 || argc < 2 ){
        fprintf(stderr, "Invalid arguments\n");
        return -1;

    } else if (argc == 2){
        // pripad kedy je zadane len meno suboru
        pocet_clustrov = load_clusters(argv[1],&(clusters));
        if (pocet_clustrov < 0 ){
            return -1;
        }
    } else {
        // posledny pripad kedy je meno aj pocet clustrov
        char *perr = NULL;
        max_clustrov = strtol(argv[2], &perr, 10);

        pocet_clustrov = load_clusters(argv[1],&(clusters));
        if ((perr != NULL && *perr !='\0') || (pocet_clustrov < max_clustrov) || (max_clustrov <= 0 ) || (pocet_clustrov <= 0 )){
            if (pocet_clustrov > 0 ){
                for(int id_cluster = 0; id_cluster < pocet_clustrov; id_cluster++){
                    clear_cluster(&clusters[id_cluster]);

                }
                free(clusters);
            }

            fprintf(stderr, "Entered valid number of clusters or some clusters parameters are faulty or input file parameter or file name is wrong\n");
            return -1;
        }
    }

    // tu prebieha hlavny program, kym pocet clustrov == max_clustrov co znamena ze program prebeho uspesne
    while (pocet_clustrov > max_clustrov){
        int i, j; // deklaracia indexov
        find_neighbours(clusters,pocet_clustrov,&i,&j); // najde najblizsie clustre a vrati ich indexy do i, j
        merge_clusters(&(clusters[i]),&(clusters[j])); // tu sa clustre zjednotia do prveho clustra
        pocet_clustrov = remove_cluster(clusters,pocet_clustrov,j); // remove_cluster vracia novy pocet_clustro v poli

    }

    print_clusters(clusters,max_clustrov);


    //vyciste vsetky mallocy, ktore boli na clusters
    for(int id_cluster = 0; id_cluster < max_clustrov; id_cluster++){
        clear_cluster(&clusters[id_cluster]);

    }



    // vycisty pole clustrov
    free(clusters);




    // TODO


}
