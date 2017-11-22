
#include <string.h>
#include <stdlib.h>
#include "bdf_font.h"

/*================================================*/

int get_str_arg(char ***argv, int c, char **result)
{
  if ( (**argv)[0] == '-' )
  {
    if ( (**argv)[1] == c )
    {
      if ( (**argv)[2] == '\0' )
      {
	(*argv)++;
	*result = **argv;
      }
      else
      {
	*result = (**argv)+2;
      }
      (*argv)++;
      return 1;      
    }
  }
  return 0;
}


int get_num_arg(char ***argv, int c, unsigned long *result)
{
  if ( (**argv)[0] == '-' )
  {
    if ( (**argv)[1] == c )
    {
      if ( (**argv)[2] == '\0' )
      {
	(*argv)++;
	*result = strtoul((**argv), NULL, 10);
      }
      else
      {
	*result = strtoul((**argv)+2, NULL, 10);
      }
      (*argv)++;
      return 1;      
    }
  }
  return 0;
}

int is_arg(char ***argv, int c)
{
  if ( (**argv)[0] == '-' )
  {
    if ( (**argv)[1] == c )
    {
      (*argv)++;
      return 1;      
    }
  }
  return 0;
}

/*================================================*/
void help(void)
{
  printf("-h        Display this help\n");
  printf("-v        Print log messages\n");
  printf("-x        Use max bbx for each selected glyph\n");
  printf("-m <map>  Unicode ASCII mapping\n");
  printf("\n");

  printf("map := <mapcmd> { \",\" <mapcmd> }\n");
  printf("mapcmd := <default> | <maprange> | <exclude>\n");
  printf("default := \"*\"\n");
  printf("maprange := <range> [  \">\" <num> ]\n");
  printf("exclude := \"~\" <range> \n");
  printf("range := <num> [ \"-\" <num> ]\n");
  printf("num := <hexnum> | <decnum>\n");
  printf("hexnum := \"$\" <hexdigit> { <hexdigit> }\n");
  printf("decnum := <decdigit> { <decdigit> }\n");
  printf("decdigit := \"0\" | \"1\" | \"2\" | \"3\" | \"4\" | \"5\" | \"6\" | \"7\" | \"8\" | \"9\"\n");
  printf("hexdigit := \"a\" | \"b\" | \"c\" | \"d\" | \"e\" | \"f\" | \"A\" | \"B\" | \"C\" | \"D\" | \"E\" | \"F\" | <decdigit>\n");
    
  printf("{ }: zero, one ore more\n");
  printf("[ ]: zero or once\n");
  printf("|: alternative\n");
  
}

/*================================================*/
/* main */

int main(int argc, char **argv)
{
  bf_t *bf;
  char *bdf_filename = NULL;
  int is_verbose = 0;
  char *map_str ="*";
  
  
  argv++;
  /*
  if ( *argv == NULL )
  {
    help();
    exit(1);
  }
  */
  for(;;)
  {
    if ( *argv == NULL )
      break;
    if ( is_arg(&argv, 'h') != 0 )
    {
      help();
      exit(1);
    }
    else if ( is_arg(&argv, 'v') != 0 )
    {
      is_verbose = 1;
    }
    /*
    else if ( get_num_arg(&argv, 's', &speed) != 0 )
    {
    }
    */
    else if ( get_str_arg(&argv, 'm', &map_str) != 0 )
    {      
    }
    else
    {
      bdf_filename = *argv;
      argv++;
    }
  }
  
  if ( bdf_filename  == NULL )
  {
    printf("bdf filename?\n");
    exit(1);
  }
  
  bf = bf_Open();
  bf->is_verbose = is_verbose;
  bf_ParseFile(bf, bdf_filename);
  bf_Map(bf, map_str);
  bf_CalculateSelectedNumberOfGlyphs(bf);
  
  bf_ReduceAllGlyph(bf);
  bf_CalculateMaxBBX(bf);
  bf_ShowAllGlyphs(bf, &(bf->max));
  bf_CalculateMinMaxDWidth(bf);
  bf_CalculateMaxBitFieldSize(bf, &(bf->max));
  bf_RLECompressAllGlyphs(bf, &(bf->max));


  tga_init(100, 80);
  tga_set_pixel(1, 1, 255,0,0);

  tga_set_font(bf->target_data);
  tga_draw_glyph(20, 20, 'A');
  
  
  tga_save("bdf.tga");


  
  bf_Close(bf);
  return 0;
}
