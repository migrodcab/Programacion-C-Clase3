#include "gestor_tarea.h"
#include <string.h>

/*static int binsearch(struct tarea *lista[], int size, struct tarea *t)
{
	int low = 0;
	int high = size - 1;
	int prioridad = curso_tarea_attr_get_u32(t, CURSO_TAREA_ATTR_PRIORIDAD);
	if (prioridad > curso_tarea_attr_get_u32(lista[high], CURSO_TAREA_ATTR_PRIORIDAD))
		return size;
	while (high > low) {
		int mid = (low + high) /2;
		if (curso_tarea_attr_get_u32(lista[mid], CURSO_TAREA_ATTR_PRIORIDAD) > prioridad)
			high = mid;
		else
			low = mid + 1;
	}
	return low;
}*/

struct gestor_tarea {
	struct list_head	tareas;

	uint32_t	num_tareas;

	uint32_t	flags;
};

struct gestor_tarea *curso_gestor_alloc(void)
{
	struct gestor_tarea *ges;
	ges = malloc(sizeof(struct gestor_tarea));
	if (ges ==  NULL)
		return NULL;

	INIT_LIST_HEAD(&ges->tareas);

	ges->flags |= (1 << CURSO_GESTOR_ATTR_NUM_TAREAS);

	return ges;
}
void curso_gestor_free(struct gestor_tarea *ges)
{
	int i;
	struct tarea *t, *tmp;
	/*for (i = 0; i < ges->num_tareas; i++)
		curso_tarea_free(ges->tareas[i]);*/
	list_for_each_entry_safe(t, tmp, &ges->tareas, head) {
		list_del(&t->head);
		curso_tarea_free(t);
	}

	xfree(ges);
}

void curso_gestor_attr_unset_tarea(struct gestor_tarea *ges,
					  uint32_t pos)
{
	int i = 0;
	struct tarea *t, *tmp;
	if (pos < 0 || pos > ges->num_tareas)
		return;

	/*curso_tarea_free(ges->tareas[pos]);
	int i;
	for ( i = pos; i < ges->num_tareas; i++) 
		ges->tareas[i] = ges->tareas[i+1];*/

	list_for_each_entry_safe(t, tmp, &ges->tareas, head) {
		if (i == pos) {
			list_del(&t->head);
			curso_tarea_free(t);
			break;
		}

		i++;
	}
	ges->num_tareas--;
}

static void curso_gestor_set_data(struct gestor_tarea *ges,
					 uint16_t attr, const void *data)
{
	//int i, pos;
	struct tarea *t;

	if (attr > CURSO_GESTOR_ATTR_MAX)
		return;

	switch (attr) {
	case CURSO_GESTOR_ATTR_TAREA:
		if (ges->num_tareas > 10) {
			printf("La lista de tareas esta llena\n");
			break;
		}
		/*if (ges->num_tareas > 0)
			pos = binsearch(ges->tareas, ges->num_tareas, (struct tarea *)data);
		else
			pos = 0;

		for (i = ges->num_tareas - 1; i >= pos; i--)
			ges->tareas[i+1] = ges->tareas[i];

		ges->tareas[pos] = (struct tarea *)data;
		ges->num_tareas++;
		break;*/
		t = (struct tarea *)data;
		list_add(&t->head, &ges->tareas);
		ges->num_tareas++;
		break;
	}

	ges->flags |= (1 << attr);
}
void curso_gestor_attr_set_str(struct gestor_tarea *ges, uint16_t attr,
				      const char *data)
{
		curso_gestor_set_data(ges, attr, data);
}
void curso_gestor_attr_set_tarea(struct gestor_tarea *ges,
					uint16_t attr, struct tarea *data)
{
	curso_gestor_set_data(ges, attr, data);
}

const void *curso_gestor_attr_get_data(struct gestor_tarea *ges,
					      uint16_t attr, uint32_t pos)
{
	int i = 0;
	struct tarea *t;
	if (!(ges->flags & (1 << attr)))
		return NULL;

	switch(attr) {
	case CURSO_GESTOR_ATTR_NUM_TAREAS:
		return &ges->num_tareas;
	case CURSO_GESTOR_ATTR_TAREA:
		list_for_each_entry(t, &ges->tareas, head) {
			if (i == pos)
				break;

			i++;
		}

		return t;
	}
	return NULL;
}

uint32_t curso_gestor_attr_get_u32(struct gestor_tarea *ges,
					  uint16_t attr)
{
	const void *ret = curso_gestor_attr_get_data(ges, attr, 0);
	return ret == NULL ? 0 : *((uint32_t *)ret);
}
const char *curso_gestor_attr_get_str(struct gestor_tarea *ges,
					     uint16_t attr)
{
	return curso_gestor_attr_get_data(ges, attr, 0);
}
struct tarea *curso_gestor_attr_get_tarea(struct gestor_tarea *ges,
						 uint16_t attr, uint32_t pos)
{
	return (struct tarea *)curso_gestor_attr_get_data(ges, attr, pos);
}

int curso_gestor_snprintf(char *buf, size_t size, struct gestor_tarea *ges)
{
	int ret = 0;
	struct tarea *t;

	ret += snprintf(buf, size,
			"La lista de tareas tiene %d y son:\n", ges->num_tareas);

	list_for_each_entry(t, &ges->tareas, head) {
		ret += curso_tarea_snprintf(buf + ret, size - ret, t);
		ret += snprintf(buf + ret, size - ret, "\n");
	}

	return ret;
}
