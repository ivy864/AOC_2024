#ifndef HT_INCLUDED
#define HT_INCLUDED


typedef struct HT_Item HT_Item;
struct HT_Item {
    char *key;
    int value;
    HT_Item *next;
};

typedef struct HashTable {
    HT_Item **items;
    int size;
    int count;

} HashTable;

/** initialize empty hashtable
 *
 * @param size size of hashtable
 */
HashTable *htInit(int size);

/* get value for specified key
 * return null if there is no value for the key
 */
int *htget(HashTable *table, char *key);

/* put value in hashtable
 */
void htput(HashTable *table, char *key, int value);

/* free contents of a hashtable
 */
void htfree(HashTable *table);

/* free hashtable item
 */
void htifree(HT_Item *item);

void htprint(HashTable *table);

#endif // !HT_INCLUDED
