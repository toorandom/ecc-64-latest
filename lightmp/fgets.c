/*
 * prueba de fgets para marcela
 */
#include <stdio.h>
#include <sys/stat.h>

#define MAX_LINE_LEN 1024	/* Es el maximo que permitiriamos de linea, generalment trata de usar numeros como este (potencias de 2 para buffers por performance) */
int
main (int argc, char **argv)
{
  FILE *fp;
  char *filename, linea[MAX_LINE_LEN], contador = 0, *verificador;
  struct stat file_info;	/* Esta estructura te sirve para saber datos de un archivo como tamanio , inodos , permisos etc... */
  if (argc < 2)
    {
      fprintf (stderr, "Error necesitas especificar un archivo\n");
      exit (EXIT_FAILURE);
    }

/* Definimos este apuntador filename como argv[1] que sera el archivo que quieres abrir */
  filename = argv[1];


/* Verificamos si el archivo existe con stat() lee manpage si algo no entiendes */
  if (stat (filename, &file_info) < 0)
    {
      perror ("stat");
      fprintf (stderr,
	       "Error en archivo , checar permisos, existencia, etc.\n");
      exit (EXIT_FAILURE);
    }


  fp = fopen (filename, "r+") if (fp == NULL)
   if(fp == NULL)
    {
      perror ("fopen");
      fprintf (stderr, "Error abriendo archivo\n");
      exit (EXIT_FAILURE);
    }


  while (verificador != NULL)
    {
      verificador = fgets ((char *) &linea, MAX_LINE_LEN, 1);

    }





}
