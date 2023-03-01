#include "ll1_gram.h"
#include "parser.h"
#include "lexer.h"

void populate_first_sets() {
  bool is_changed = true;
  int lhs;
  rhs* rhs_ptr;
  while (is_changed == true) { // traverse until convergence
 
	is_changed = false;
	for (int i = 0; i < NUM_OF_RULES; i++) {
	  lhs = G[i].lhs_id;
	  rhs_ptr = G[i].firstRHS;
	  if ((rhs_ptr->isTerminal) == true){ // if terminal, add it and move ahead

		int t = rhs_ptr->rhs_id;
		First[lhs][t] = 1; 
		is_changed = true;
		
	  } 
	  else { // nonterminal
		rhs* temp = rhs_ptr;
		// int *rhs_symbol_fset;
		// ull *lhs_symbol_fset = first_set[lhs];
		while (temp != NULL){ // traverse till end of the rule
		  if (temp->isTerminal == true){
			int t = temp->rhs_id; 
			First[lhs][t] = 1; 
			is_changed = true; 
			break;
		  }

		  bool is_diff = false;
		  bool eps_in_rhs = false;
		  bool eps_in_lhs = false;

		  if (First[temp->rhs_id][NUM_OF_TERMINALS-1]==1){ // remove epsilon from current nt before checking things
			eps_in_rhs = true;
			set_remove_elem(rhs_symbol_fset, EPSILON);
		  }

		  if (set_find_elem(lhs_symbol_fset, EPSILON) == true) {
			eps_in_lhs = true;
		  }

		  if (is_superset(lhs_symbol_fset, rhs_symbol_fset) ==
			  false) // rhs nt has a terminal which lhs nt does not
					 // have in it's fset
		  {
			is_changed = true;
			set_union(lhs_symbol_fset, lhs_symbol_fset, rhs_symbol_fset);

			if (eps_in_rhs ==
				false) // if rhs nt does not have eps, no need to go further
			{
			  break;
			} else {
			  set_add_elem(rhs_symbol_fset, EPSILON); // set eps back to rhs nt
			  if (eps_in_lhs == false) {
				if (temp->next == NULL) // only add eps to lhs nt if rhs is last
										// nt in the rule
				{
				  set_add_elem(lhs_symbol_fset, EPSILON);
				  is_changed = true;
				}
			  }
			}
		  } else // if is_diff == false, break;
		  {
			if (eps_in_rhs == true) {
			  set_add_elem(rhs_symbol_fset, EPSILON); // set eps back to rhs nt
			  if (eps_in_lhs == false) {
				if (temp->next == NULL) // only add eps to lhs nt if rhs is last
										// nt in the rule
				{
				  set_add_elem(lhs_symbol_fset, EPSILON);
				  is_changed = true;
				}
			  }
			}
			break; //
		  }
		  temp = temp->next;
		} // end of rule linked list traversal while loop
	  }   // end of else (non-terminal branch)
	}     // end of for - grammar traversal
  }       // end of while - infinite loop until convergence
} 