#include <stdio.h>
#define BOOL short int
#define TRUE 1
#define FALSE 0

typedef struct {
	int from;
	int to;
	char with;
} transition;

typedef struct {
	char* alphabets;
	unsigned int alphabet_count;

	transition* transitions;
	unsigned int transitions_count;

	int initial_state;
	
	int* states;
	unsigned int states_count;
	
	int* final_states;
	unsigned int final_state_count;
} dfa_t ;

transition* get_transition(int state, char alphabet, dfa_t* dfa) {
	for (unsigned int i = 0; i < dfa->transitions_count; i++) {
		transition* current_transition = &(dfa->transitions[i]);
		if (current_transition->with == alphabet && current_transition->from == state) return current_transition;
	}
	return NULL;
}

BOOL is_final_state(int state, dfa_t* dfa) {
	for (unsigned int i = 0; i < dfa->final_state_count; i++) {
		if (state == dfa->final_states[i]) return TRUE;
	}
	return FALSE;
}

BOOL is_valid(dfa_t *dfa, char* input_string) {
	int current_state = dfa->initial_state;
	char* current_alphabet = input_string;

	while (*current_alphabet != '\0') {
		transition* current_transition = get_transition(current_state, current_alphabet, dfa);
		printf("%d -> %d with %c\n", current_transition->from, current_transition->to, current_transition->with);
		
		if (current_transition == NULL)
			return FALSE;

		current_state = current_transition->to;
		current_alphabet++;
	}

	return is_final_state(current_state, dfa);
}

void main() {
	char sigma[] = { 'a', 'b' };
	transition transitions[] = {
		(transition) { 0, 1, 'a' },
		(transition) { 0, 2, 'b' },
		(transition) { 1, 1, 'b' },
		(transition) { 1, 2, 'a' },
		(transition) { 2, 2, 'a' },
		(transition) { 2, 2, 'b' },
	};
	int final_states[] = {1};
	int states[] = { 0, 1, 2 };

	dfa_t dfa;
	dfa.alphabets = sigma;
	dfa.alphabet_count = 2;
	dfa.transitions = transitions;
	dfa.transitions_count = 6;
	dfa.initial_state = 0;
	dfa.final_states = final_states;
	dfa.final_state_count = 1;
	dfa.states = states;
	dfa.states_count = 3;

	char* input = "abb";

	if (is_valid(&dfa, input)) printf("%s is valid.", input);
	else printf("%s is invalid", input);
}
