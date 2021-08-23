#include "Hash_Map.h"
//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main ()
{
    struct hash_map Hash_Map = {NULL, 0};

    Hash_Map = Init_Hash_Map ();
    
    printf ("Vscadwd\n");
    for (int i = 0; i < 300000; i++)
        Insert_Hash_Map (&Hash_Map, i);

    int res = Hash_of_Data (59);
    printf ("RES = %d\n", res);

    printf ("Hash_Map.cells[670].items->data_t = %d", Hash_Map.cells[res].next->item->data_t);
    Free_Hash_Map (Hash_Map);
}