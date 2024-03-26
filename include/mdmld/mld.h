#ifndef MLD_H
#define MLD_H

#include "md_api.h"

#include <assert.h>
#include <stdlib.h>
#include <stdint.h>

/* ------------------------------------ Macros ------------------------------------ */

/// Max size of structure and field names
#define MAX_STRUCTURE_NAME_SIZE 128
#define MAX_FIELD_NAME_SIZE 128

/// Convert integer to void pointer
#define INT2VOIDP(i) (void*)(uintptr_t)(i)

/// Count of elements in an array
#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))


/// Get the offset of a field in a structure
#define OFFSETOF(struct_name, fld_name)     \
          (unsigned long)&(((struct_name *)NULL)->fld_name)

/// Get the size of a field in a structure
#define FIELD_SIZE(struct_name, fld_name)   \
          sizeof(((struct_name *)NULL)->fld_name)


/// Generate a field information structure
#define FIELD_INFO(struct_name, fld_name, dtype, nested_struct_name)        \
            { #fld_name, dtype, FIELD_SIZE(struct_name, fld_name),          \
            OFFSETOF(struct_name, fld_name), #nested_struct_name } 

/// Register a structure in the structure database
#define REG_STRUCT(struct_db, st_name, fields_arr)                            \
            do{                                                               \
                struct_db_rec_t *rec = calloc(1, sizeof(struct_db_rec_t));    \
                strncpy(rec->struct_name, #st_name, MAX_STRUCTURE_NAME_SIZE); \
                rec->ds_size  = sizeof(st_name);                              \
                rec->n_fields = sizeof(fields_arr)/sizeof(field_info_t);      \
                rec->pFields  = fields_arr;                                   \
                if (add_to_struct_db(struct_db, rec)) assert(0);              \
            } while(0);

/* ------------------------------------ Enumarations ------------------------------------ */

/** Enumarate for data types */
typedef MD_API enum
{
    UINT8,
    UINT32,
    INT32,
    CHAR,
    OBJ_PTR,
    FLOAT,
    DOUBLE,
    OBJ_STRUCT,

    TYPES_COUNT = 8
} data_type_t;

/* ------------------------------------ Data structures ------------------------------------ */

/** Structure to store the information of a field of a structure */
typedef struct _field_info
{
    char         fname [MAX_FIELD_NAME_SIZE]; // Field name
    data_type_t  dtype;                       // Data type of the field
    unsigned int size;                        // Size of the field
    unsigned int offset;                      // Offset of the field

    /// If the field is a pointer to structure, then store the structure name
    char         nested_str_name[MAX_STRUCTURE_NAME_SIZE];
} field_info_t;


typedef struct _struct_db_rec_t struct_db_rec_t;

/** Store the information of a struct with 'n' fields */
typedef struct _struct_db_rec_t
{
    struct_db_rec_t *pNext;                                 // Pointer to the next structure in the list
    char             struct_name[MAX_STRUCTURE_NAME_SIZE];  // Key
    unsigned int     ds_size;                               // Size of the structure
    unsigned int     n_fields;                              // Number of fields in the structure
    field_info_t    *pFields;                               // Pointer to the fields array
} struct_db_rec_t;

/** Store the information of all the structures in the application */
typedef struct _struct_db_t
{
    struct_db_rec_t *pHead; // Pointer to the head
    unsigned int     count; // Number of structures
} struct_db_t;


typedef struct _object_db_rec_ object_db_rec_t;

/** Store the information of an object that was allocated */
struct _object_db_rec_
{
    void        *ptr;        // Pointer to the object that was allocated
    unsigned int units;      // Number of objects of this type
    struct_db_rec_t *pRec;   // Pointer to the structure record
    object_db_rec_t *pNext;  // Pointer to the next structure in the list
};

/** Store the information of all the objects that were allocated */
typedef struct _object_db_
{
    object_db_rec_t *pHead; // Pointer to the head
    struct_db_t     *pDB;   // Pointer to the structure database
    unsigned int     count; // Number of objects
} object_db_t;

/** ------------------------------------ Print functions ------------------------------------ */ 

/** Print the information of a structure record */
void print_structure_rec(struct_db_rec_t *struct_rec);

/** Print the information of all the structures in the structure database */
void print_structure_db(struct_db_t *struct_db);

/** Print the information of an object record */
void print_object_rec(object_db_rec_t *object_rec, int i);

/** Print the information of all the objects in the object database */
void print_object_db(object_db_t *object_db);

/** ------------------------------------ DB functions --------------------------------------- */ 

/** Add a structure record to the structure database */
int add_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);


/** ------------------------------------ MLD functions --------------------------------------- */

/**
 * Allocate memory and initialize the structure database.
 * @param struct_db Pointer to the structure database
 * @param struct_name Name of the structure
 * @param units Number of objects to allocate
 * @return Pointer to the structure database
 */
void* xcalloc(object_db_t *object_db, char *struct_name, int units);


#endif // MLD_H

