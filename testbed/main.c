#include <memory.h>
#include <stdlib.h>

#include "mdmld/mdmld.h"

typedef struct transform
{
   float x, y;
} transform_t;

/** Holds a generic game object */
typedef struct game_object
{
   char               *name;
   int                 id;
   transform_t         transform;
   struct game_object *pNext;
} game_object_t;

// another structute example
typedef struct player
{
   char          *name;
   int            id;
   unsigned int   health;
   unsigned int   mana;
   transform_t    transform;
   struct player *pNext;
} player_t;

int
main()
{
   // Allocate memory for the structure database
   struct_db_t *struct_db = calloc(1, sizeof(struct_db_t));
   
   // Register the game_object_t structure
   static field_info_t emp_fields[] =
   {
      FIELD_INFO(game_object_t, name,      CHAR,       0),
      FIELD_INFO(game_object_t, id,        INT32,      0),
      FIELD_INFO(game_object_t, transform, OBJ_STRUCT, transform),
      FIELD_INFO(game_object_t, pNext,     OBJ_PTR,    game_object)
   };
   REG_STRUCT(struct_db, game_object_t, emp_fields);

   // Register the player_t structure
   static field_info_t player_fields[] =
   {
      FIELD_INFO(player_t, name,      CHAR,       0),
      FIELD_INFO(player_t, id,        INT32,      0),
      FIELD_INFO(player_t, health,    UINT32,     0),
      FIELD_INFO(player_t, mana,      UINT32,     0),
      FIELD_INFO(player_t, transform, OBJ_STRUCT, transform),
      FIELD_INFO(player_t, pNext,     OBJ_PTR,    player)
   };
   REG_STRUCT(struct_db, player_t, player_fields);

   // Print the structure database
   print_structure_db(struct_db);

   return 0;
}

