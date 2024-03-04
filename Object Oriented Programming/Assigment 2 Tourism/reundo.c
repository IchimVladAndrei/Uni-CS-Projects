#include "reundo.h"
#include "repo.h"
#include <stdio.h>
#include <stdlib.h>
UndoRedo* createUndoRepo(int size, Repos* repo)
{
	UndoRedo* undoredo = (UndoRedo*)malloc(sizeof(UndoRedo));
	if (undoredo == NULL)
		return NULL;
	undoredo->count = 0;
	undoredo->max_len = size;
	undoredo->current_pos = 0;
	undoredo->total_op = 0;
	undoredo->data = (Repos*)malloc(size * sizeof(Repos));

	if (undoredo->data == NULL)
		return NULL;
	undoredo->data[undoredo->current_pos] = duplicate(repo);

	return undoredo;
}

void destroy_reundo(UndoRedo* undoredo)
{
	if (undoredo == NULL)
		return;
	for (int i = 0; i <= undoredo->count; i++)
		free(undoredo->data[i].array.data);
	free(undoredo->data);
	undoredo->data = NULL;
	free(undoredo);
}

void resize_reundo(UndoRedo* undoredo)
{
	undoredo->data = (Repos*)(realloc(undoredo, sizeof(Repos) * undoredo->max_len * 2));
	undoredo->max_len = undoredo->max_len * 2;
}

void add_reundo(UndoRedo* undoredo, Repos* repo)
{
	if (undoredo == NULL)
		return;
	if (undoredo->data == NULL)
		return;
	if (undoredo->max_len == undoredo->current_pos)
		resize_reundo(undoredo);
	undoredo->current_pos++;
	undoredo->count++;
	undoredo->total_op = undoredo->current_pos;
	undoredo->data[undoredo->current_pos] = duplicate(repo);

}

int undo_op(UndoRedo* undoredo)
{
	if(undoredo->current_pos==0)
		return 0;
	undoredo->current_pos--;
	return 1;
}

int redo_op(UndoRedo* undoredo)
{
	if(undoredo->current_pos==undoredo->total_op)

		return 0;
	undoredo->current_pos++;
	return 1;
}
