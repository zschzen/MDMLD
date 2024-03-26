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


/** ------------------------------------ Print functions ------------------------------------ */ 

/** Print the information of a structure record */
MD_API void print_structure_rec(struct_db_rec_t *struct_rec);

/** Print the information of all the structures in the structure database */
MD_API void print_structure_db(struct_db_t *struct_db);


/** ------------------------------------ DB functions --------------------------------------- */ 

/** Add a structure record to the structure database */
MD_API int add_to_struct_db(struct_db_t *struct_db, struct_db_rec_t *struct_rec);

#endif // MLD_H

