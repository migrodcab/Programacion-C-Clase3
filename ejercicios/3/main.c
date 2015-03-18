#include "concesionario.h"
#include <string.h>
#include <getopt.h>
int leeFichero(char *file, struct concesionario * con)
{
	FILE *fp;
	char line[300];
	struct coche *c;

	fp = fopen(file, "r");

	if (fp == NULL) {
		printf("Error (NO ABIERTO)\n");
		return -1;
	}

	while (fgets(line, sizeof(line), fp)) {
		char *p;
		int i = 0;
		c = curso_coche_alloc();
		p = strtok(line, ",");
		while (p != NULL) {
			switch (i) {
			case 0:
				curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MATRICULA, p);
				break;
			case 1:
				curso_coche_attr_set_str(c, CURSO_COCHE_ATTR_MARCA, p);
				break;
			case 2:
				curso_coche_attr_set_u32(c, CURSO_COCHE_ATTR_ID, atoi(p));
				break;
			default:
				break;
			}
			i++;
			p = strtok(NULL, ",");
		}
		curso_concesionario_attr_set_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, c);
	}

	if (fclose(fp)) {
		printf("Error: fichero NO CERRADO\n");
		return -1;
	}
	return 0;
}


int escribeFichero(char *file, struct concesionario * con)
{
	FILE *fp;
	char line[300];
	struct coche *c;
	int i;

	fp = fopen(file, "w");
	if (fp == NULL) {
		printf("Error (NO ABIERTO)\n");
		return -1;
	}

	for (i = 0; i< curso_concesionario_attr_get_u32(con, CURSO_CONCESIONARIO_ATTR_NUM_COCHES); i++) {
		c = curso_concesionario_attr_get_coche(con, CURSO_CONCESIONARIO_ATTR_COCHE, i);
		char id[10];
		sprintf(id, "%d", curso_coche_attr_get_u32(c, CURSO_COCHE_ATTR_ID));
		fputs(curso_coche_attr_get_str(c, CURSO_COCHE_ATTR_MATRICULA), fp);
		fputc(',', fp);
		fputs(curso_coche_attr_get_str(c, CURSO_COCHE_ATTR_MARCA), fp);
		fputc(',', fp);
		fputs(id, fp);
		fputc('\n', fp);
	}

	if (fclose(fp)) {
		printf("Error: fichero NO CERRADO\n");
		return -1;
	}

	return 0;
}


int main(int argc, char *argv[])
{
	struct concesionario *con;
	char info[5000];
	con = curso_concesionario_alloc();
	curso_concesionario_attr_set_str(con, CURSO_CONCESIONARIO_ATTR_DUENO, "Miguel");
	int val, option_index = 0;
	static struct option long_options[] = {
		{ "file", required_argument, 0, 'f' },
		{ 0 }
	};

	val = getopt_long(argc, argv, "f:", long_options, &option_index);
	if (val == -1){
		curso_concesionario_free(con);
		return val;
	}

	switch (val) {
	case 'f':
		leeFichero(optarg, con);
		break;
	default:
		printf("Debe usar el parametro -f/--file\n");
		break;
	}

	curso_concesionario_snprintf(info, sizeof(info), con);
	printf("%s", info);
	escribeFichero("escritura.dat", con);
	curso_concesionario_free(con);
	return 0;
}
