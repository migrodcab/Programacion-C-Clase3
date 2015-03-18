#include "concesionario.h"
#include <stdio.h>
#include <getopt.h>


int main(int argc, char *argv[])
{

	struct concesionario *con;
	struct coche *c;
	char info[4000];
	int val, option_index = 0;
	char *str;
	int aux_int;

	static struct option long_options[] = {
		{ "matricula", required_argument, 0, 'm' },
		{ "id", required_argument, 0, 'i' },
		{ "gama", required_argument, 0, 'g' },
		{ "dueno", required_argument, 0, 'd' },
		{ "ayuda", required_argument, 0, 'h' },
		{ 0 }
	};

	c = curso_coche_alloc();
	con = curso_concesionario_alloc();
	str = malloc(15*sizeof(char));
	
	while (1) {
		val = getopt_long(argc, argv, "m:i:g:d:h:", long_options, &option_index);
		if (val == -1)
			//return val;
			break;

		switch (val) {
		case 'm':
			printf("Opcion matricula\n");
			str = optarg;
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MATRICULA, str);
			break;
		case 'i':
			printf("Opcion id\n");
			aux_int = atoi(optarg);
			curso_coche_attr_set_u32(c, CURSO_COCHE_ATTR_ID, aux_int);
			break;
		case 'g':
			printf("Opcion gama\n");
			str = optarg;
			curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MARCA, str);
			break;
		case 'd':
			printf("Opcion dueño\n");
			str = optarg;
			curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO, str);
			break;
		case 'h':
			printf("Uso: nombrePrograma [-m/--matricula] [-i/--id]"
				" [-g/--gama] [-d/--dueno] o [-h/--help]\n\n"
				"m -> matrícula de nuestro vehículo\n"
				"i -> id de nuestro coche\n"
				"g -> gama o marca del vehículo\n"
				"d -> dueño del concesionario\n"
				"h -> Ayuda con el uso correcto del programa"
				" y los parámetros aceptados\n");
			break;
		default:
			printf("introduzca -h si necesita ayuda\n");
			break;
		}
	}


	curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, c);
	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);

	curso_concesionario_free(con);
	return 0;
}
