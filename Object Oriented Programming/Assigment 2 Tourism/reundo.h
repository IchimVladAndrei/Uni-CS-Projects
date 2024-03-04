#pragma once
#include "repo.h"

typedef struct {
	Repos* data;
	int count, max_len, current_pos, total_op;
}UndoRedo;
/// <summary>
/// This function allows us to create an undo redo repo where we add what changes have been made to the repo.
/// </summary>
/// <param name="size">What size to prepare for</param>
/// <param name="repo">The repo which has the offers</param>
/// <returns></returns>
UndoRedo* createUndoRepo(int size, Repos* repo);

/// <summary>
/// This function destroys the undo redo repo
/// </summary>
/// <param name="undoredo"></param>
void destroy_reundo(UndoRedo* undoredo);
/// <summary>
/// This function resizes the repo if called
/// </summary>
/// <param name="undoredo"></param>
void resize_reundo(UndoRedo* undoredo);
/// <summary>
/// This function adds a new state of the repo of offers
/// </summary>
/// <param name="undoredo">repo</param>
/// <param name="repo"> with offers</param>
void add_reundo(UndoRedo* undoredo, Repos* repo);
/// <summary>
/// This function does the undo
/// </summary>
/// <param name="undoredo"></param>
/// <returns>0 if no undo possible,1 if an undo was made</returns>
int undo_op(UndoRedo* undoredo);
/// <summary>///This function does the redo /// </summary>/// <param name="undoredo"></param>/// <returns>0 if no redo possible,1 if a redo was made</returns>
int redo_op(UndoRedo* undoredo);