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
   game_object_t go;
   unsigned int  health;
   unsigned int  mana;
} player_t;

int
main(void)
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
      FIELD_INFO(player_t, go,      OBJ_PTR,  game_object),
      FIELD_INFO(player_t, health,  UINT32,   0),
      FIELD_INFO(player_t, mana,    UINT32,   0),
   };
   REG_STRUCT(struct_db, player_t, player_fields);

   // Print the structure database
   print_structure_db(struct_db);

   object_db_t *object_db = calloc(1, sizeof(object_db_t));
   object_db->pDB = struct_db;

   // Allocate memory for the player object
   player_t *player1 = xcalloc(object_db, "player_t", 1);
   player_t *player2 = xcalloc(object_db, "player_t", 1);

   // Allocate memory for the game object
   game_object_t *go1 = xcalloc(object_db, "game_object_t", 2);

   // Print the object database
   print_object_db(object_db);

   return 0;
}

