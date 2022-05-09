#include <stdlib.h>
#include <string.h>

#include "memory.h"
#include "object.h"
#include "table.h"
#include "value.h"

#define TABLE_MAX_LOAD 0.75

// Creates an empty table
void initTable(Table* table){
    table->count = 0;
    table->capacity = 0;
    table->entries = NULL;
}

// Frees a table
void freeTable(Table* table){
    FREE_ARRAY(Entry, table->entries, table->capacity);
    initTable(table);
}
// Finds an entry or creates a new one with a key and capacity
static Entry* findEntry(Entry* entries, int capacity, ObjString* key){
    uint32_t index = key->hash % capacity;
    Entry* tombstone = NULL;
    for(;;){
        Entry*  entry = &entries[index];
        if(entry->key == NULL){
            if(IS_NIL(entry->value)){
                // empty entry
                return tombstone != NULL ? tombstone : entry;
            } else {
                // we found a tombstone
                if(tombstone == NULL) tombstone = entry;
            }
        } else if (entry->key == key){
            // we found the key
            return entry;
        }
        index = (index + 1) % capacity;
    }
}
static void adjustCapacity(Table* table, int capacity){
    Entry* entries = ALLOCATE(Entry, capacity);
    for(int i = 0; i < capacity; i++){
        entries[i].key = NULL;
        entries[i].value = NIL_VAL;
    }
    for(int i = 0; i < table->capacity; i++){
        Entry* entry = &table->entries[i];
        if(entry->key == NULL) continue;

        Entry* dest = findEntry(entries, capacity, entry->key);
        dest->key = entry->key;
        dest->value = entry->value;
    }
    FREE_ARRAY(Entry, table->entries, table->capacity);
    table->entries = entries;
    table->capacity = capacity;
}

bool tableGet(Table* table, ObjString* key, Value* value){
    if(table->count == 0) return false;

    Entry* entry = findEntry(table->entries, table->capacity, key);
    if(entry->key == NULL) return false;

    *value = entry->value;
    return true;
}

// Adds a new entry into the table
bool tableSet(Table* table, ObjString* key, Value value){
    // Check if the array is at max load
    if(table->count+1 > table->capacity * TABLE_MAX_LOAD){
        int capacity = GROW_CAPACITY(table->capacity);
        adjustCapacity(table, capacity);
    }

    // Find the entry
    Entry* entry = findEntry(table->entries, table->capacity, key);
    // Checks if the entry's key already exists
    bool isNewKey = entry->key == NULL;
    // if it is new key, the count increases
    if(isNewKey) table->count++;

    entry->key = key;
    entry->value = value;
    return isNewKey;
}

// Removes an entry
bool tableDelete(Table* table, ObjString* key){
    // check if table is empty
    if(table->count == 0) return false;
    // find the entry
    Entry* entry = findEntry(table->entries, table->capacity, key);
    if(entry->key == NULL) return false;

    // Place a tombstone in the entry
    entry->key = NULL;
    entry->value = BOOL_VAL(true);
    return true;
}

// Copies all of one table's hash entries to another
void tableAddAll(Table* from, Table* to){
    for(int i = 0; i < from->capacity; i++){
        Entry* entry = &from->entries[i];
        if(entry->key != NULL){
            tableSet(to, entry->key, entry->value);
        }
    }
}
