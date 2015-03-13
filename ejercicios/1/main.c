#include "gestor_tarea.h"

int main(void)
{
	struct tarea *t1, *t2, *t3;
	struct gestor_tarea *ges;
	char info[4000];

	t1 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_NOMBRE, "Limpiar");
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_DES, "Barrer la cocina");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_ID, 2);
	curso_tarea_attr_set_str(t1, CURSO_TAREA_ATTR_USUARIO, "Miguel");
	curso_tarea_attr_set_u32(t1, CURSO_TAREA_ATTR_PRIORIDAD, 2);

	t2 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_NOMBRE, "Fregar");
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_DES, "Fregar los platos");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_ID, 0);
	curso_tarea_attr_set_str(t2, CURSO_TAREA_ATTR_USUARIO, "Manolo");
	curso_tarea_attr_set_u32(t2, CURSO_TAREA_ATTR_PRIORIDAD, 0);

	t3 = curso_tarea_alloc();

	curso_tarea_attr_set_str(t3, CURSO_TAREA_ATTR_NOMBRE, "Comprar");
	curso_tarea_attr_set_str(t3, CURSO_TAREA_ATTR_DES, "Ir a a la tienda");
	curso_tarea_attr_set_u32(t3, CURSO_TAREA_ATTR_ID, 1);
	curso_tarea_attr_set_str(t3, CURSO_TAREA_ATTR_USUARIO, "Antonio");
	curso_tarea_attr_set_u32(t3, CURSO_TAREA_ATTR_PRIORIDAD, 1);

	ges = curso_gestor_alloc();


	curso_gestor_attr_set_tarea(ges, CURSO_GESTOR_ATTR_TAREA,
					   t1);

	curso_gestor_attr_set_tarea(ges, CURSO_GESTOR_ATTR_TAREA,
					   t2);

	curso_gestor_attr_set_tarea(ges, CURSO_GESTOR_ATTR_TAREA,
					   t3);

	curso_gestor_snprintf(info, sizeof(info), ges);
	printf("%s", info);

	curso_gestor_attr_unset_tarea(ges, 2);

	curso_gestor_snprintf(info, sizeof(info), ges);
	printf("%s", info);
	
	curso_gestor_free(ges);
	return 0;
}
