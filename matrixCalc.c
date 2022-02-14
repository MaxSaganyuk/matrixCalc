// May 2018 - Matrix Calculator. Second Homework for Programing.
#include <stdio.h>
#include <stdlib.h> // for srand, rand
#include <string.h> // for strcmp, strcpy, strcat
#include <time.h> // for
#define _CRT_SECURE_NO_WARNINGS

#define C_SIZE 100
#define BUFF_SIZE 1024

struct Matrix {
	int val;
	int marker;
	struct Matrix *next;
};

struct M_Count {
	char name[C_SIZE];
	struct M_Count *next;
	struct Matrix *matrix;
};

int checked_input();
void helpf();
void print_Matrix(struct Matrix *current);
struct Matrix *find_m(struct Matrix *current, int which);
struct Matrix *find_s(struct M_Count *current, struct Matrix *matrix, char *name);
struct Matrix *add_s(struct M_Count *current, struct Matrix *matrix, char* name);
void delete_m(struct Matrix *matrix);
void proto_delete_m(struct M_Count *current);
int count_markers(struct Matrix *current);
int count_length(struct Matrix *current);
int mini_det(struct Matrix *current);
int det(struct Matrix *matrix, int minor_val);
void new_s(struct Matrix *current, int val, int l, int h, struct M_Count *current_2, char *name);
void keyb_enter(struct M_Count *head_2, char *proto_arg);
void save_m(struct M_Count *current);
void file_m(struct M_Count *current);
void edit_m(struct M_Count *current);
void arith_m(struct M_Count *current, int choice);
void mini_main(struct M_Count *head_2);


void save_m(struct M_Count *current) {
	FILE *f;
	struct Matrix *matrix = NULL;

	char name[C_SIZE];

	printf("Enter name of Matrix\n");
	scanf("%s", name);

	matrix = find_s(current, matrix, name);

	f = fopen(strcat(name, ".txt"), "w");
	while (matrix != NULL) {
		fprintf(f, "%i ", matrix->val);
		if (matrix->marker == 1) {
			fprintf(f, "\n");
		}
		matrix = matrix->next;
	}
	fclose(f);
}

struct Matrix *add_s(struct M_Count *current, struct Matrix *matrix, char* name) {
	struct M_Count *new = NULL;

	while (1) {
		if (current->next == NULL || strcmp(current->name, name) == 0) {
			matrix = (struct Matrix *)malloc(sizeof(struct Matrix));
			matrix->next = NULL;
			strcpy(current->name, name);
			current->matrix = matrix;
			new = (struct M_Count *)malloc(sizeof(struct M_Count));
			new->next = NULL;
			current->next = new;
			break;
		}
		else current = current->next;
	}
	return matrix;
}

void arith_m(struct M_Count *current, int choice) {
	struct Matrix *matrix1 = NULL;
	struct Matrix *matrix2 = NULL;
	struct Matrix *matrix3 = NULL;
	struct Matrix *new = NULL;
	struct M_Count *new_2 = NULL;

	char name[C_SIZE];

	int m_count;
	int l_count;
	int m_count2;
	int l_count2;

	printf("Enter First Matrix\n");
	printf("Enter -1 to abort\n");
	while (1) {
		scanf("%s", name);
		if (strcmp(name, "-1") == 0) {
			return;
		}
		matrix1 = find_s(current, matrix1, name);
		if (matrix1 == NULL) {
			printf("No Such Matrix\n");
			return;
		}
		break;
	}
	m_count = count_markers(matrix1);
	l_count = count_length(matrix1);
	printf("Enter Second Matrix\n");
	while (1) {
		scanf("%s", name);
		if (strcmp(name, "-1") == 0) {
			return;
		}

		matrix2 = find_s(current, matrix2, name);
		if (matrix2 == NULL) {
			printf("No such matrix\n");
			return;
		}
		break;
	}
	m_count2 = count_markers(matrix2);
	l_count2 = count_length(matrix2);
	printf("Enter name of the resulting matrix\n");
	scanf("%s", name);


	if (choice != 2) {
		if (m_count == m_count2 && l_count == l_count2) {

			matrix3 = add_s(current, matrix3, name);

			for (int i = 0; ; i++) {
				// choice will change depending on Sum or Reduce
				matrix3->val = matrix1->val + (choice * matrix2->val);
				matrix3->marker = 0;
				if (matrix1->marker == 1) matrix3->marker = 1;
				if (matrix1->next == NULL) break;
				new = (struct Matrix *)malloc(sizeof(struct Matrix));
				new->next = NULL;
				matrix3->next = new;
				matrix1 = matrix1->next;
				matrix2 = matrix2->next;
				matrix3 = matrix3->next;
			}
		}
		else {
			printf("These Matrices are not the same length and height\n");
			printf("Please re-enter command\n");
			return;
		}
	}
	else {
		struct Matrix *mem_matrix1 = NULL;
		struct Matrix *mem_matrix2 = NULL;
		mem_matrix1 = matrix1;
		mem_matrix2 = matrix2;

		matrix3 = add_s(current, matrix3, name);

		if (l_count == m_count2) {
			for (int i = 0; ; i++) {
				for (int j = 0; ; j++) {
					matrix3->val = 0;

					for (int k = 0; k < l_count; k++) {
						matrix1 = mem_matrix1;
						matrix2 = mem_matrix2;
						matrix3->marker = 0;

						matrix1 = find_m(matrix1, i * l_count + k);
						matrix2 = find_m(matrix2, k * l_count2 + j);
						matrix3->val += (matrix1->val * matrix2->val);
					}
					if (j == l_count2 - 1) break;
					new = (struct Matrix *)malloc(sizeof(struct Matrix));
					new->next = NULL;
					matrix3->next = new;
					matrix3 = matrix3->next;
				}
				matrix3->marker = 1;
				if (i == m_count - 1) break;
				new = (struct Matrix *)malloc(sizeof(struct Matrix));
				new->next = NULL;
				matrix3->next = new;
				matrix3 = matrix3->next;
			}
			matrix3->next = NULL;
		}
		else {
			printf("Length of first matrix must be same as Height of the second one\n");
			printf("Please re-enter command\n");
			return;
		}
	}
}

int checked_input() {
	char name[C_SIZE];

	while (1) {
		scanf("%s", name);
		if (name[0] == '0') return 0;

		if (atoi(name) != 0) return atoi(name);
	}
}

int count_length(struct Matrix *current) {
	int count = 0;

	while (current->marker != 1) {
		count++;
		current = current->next;
	}
	return ++count;
}

int count_markers(struct Matrix *current) {
	int count = 0;

	while (current->next != NULL) {
		if (current->marker == 1) count++;
		current = current->next;
	}
	return ++count;
}

void proto_delete_m(struct M_Count *current) {

	while (current->next != NULL) {
		free(current->matrix);
		free(current);
	}
}

int det(struct Matrix *matrix, int minor_val) {

	struct Matrix *mem_matrix = NULL;
	mem_matrix = matrix;

	while (matrix->marker != 1) {
		matrix->val *= minor_val;
		matrix = matrix->next;
	}
	matrix->val *= minor_val;
	matrix = mem_matrix;

	int grand_result = 0;

	int m_count;
	int l_count;

	m_count = count_markers(matrix);
	l_count = count_length(matrix);

	if (m_count != l_count) {
		printf("Matrix should be a square\n");
		return 0;
	}
	if (m_count == 2) {
		return mini_det(matrix);
	}

	struct Matrix *new = NULL;
	struct Matrix *new_matrix = NULL;
	struct Matrix *mem_new_matrix = NULL;

	for (int i = 0; i < l_count; i++) {
		matrix = find_m(mem_matrix, i);
		minor_val = matrix->val;

		new_matrix = (struct Matrix *)malloc(sizeof(struct Matrix));
		mem_new_matrix = new_matrix;
		new_matrix->next = NULL;

		for (int j = 0; ; j++) {
			for (int k = 0; ; k++) {
				new_matrix->marker = 0;
				if (i == k) k++;
				matrix = find_m(mem_matrix, (j + 1) * l_count + k);
				new_matrix->val = matrix->val;
				if (i == l_count - 1 && k == l_count - 2) break;
				if (k == l_count - 1) break;
				new = (struct Matrix *)malloc(sizeof(struct Matrix));
				new->next = NULL;
				new_matrix->next = new;
				new_matrix = new_matrix->next;
			}
			new_matrix->marker = 1;
			if (j == m_count - 2) break;
			new = (struct Matrix *)malloc(sizeof(struct Matrix));
			new->next = NULL;
			new_matrix->next = new;
			new_matrix = new_matrix->next;
		}

		new_matrix->next = NULL;
		if (i % 2 == 0) grand_result += det(mem_new_matrix, minor_val);

		else grand_result += ((-1) * det(mem_new_matrix, minor_val));
	}
	return grand_result;
}

void edit_m(struct M_Count *current) {

	struct Matrix *matrix = NULL;
	struct Matrix *matrix_current = NULL;

	int l;
	int h;
	int h_max = 0;
	char name[C_SIZE];

	printf("Enter name of matrix to edit\n");
	scanf("%s", name);

	matrix = find_s(current, matrix, name);

	matrix_current = matrix;

	h_max = count_markers(matrix_current);

	while (1) {
		matrix_current = matrix;

		print_Matrix(matrix);

		printf("\nEnter a place to change (IxJ)\n");
		printf("Enter 0 for any of parameters to abort\n");
		scanf("%ix%i", &l, &h);
		if (l == 0 || h == 0) break;


		matrix_current = matrix;

		for (int i = 0; i < (h - 1) * h_max + (l - 1); i++) {
			matrix_current = matrix_current->next;
		}
		printf("Enter a value to put\n");
		scanf("%i", &matrix_current->val);
	}
}


void file_m(struct M_Count *current) {
	FILE *f;
	struct Matrix *matrix = NULL;
	struct Matrix *new = NULL;
	struct M_Count *new_2 = NULL;

	char name[C_SIZE];
	char buff = ' ';
	char buff_arr[BUFF_SIZE] = "";
	int space_count = 0;
	int line_count = 0;

	printf("Enter name of file (for q.txt enter q)\n");
	scanf("%s", name);


	matrix = add_s(current, matrix, name);
	strcat(name, ".txt");
	f = fopen(name, "r");
	if (f != NULL) {

		while (fgets(buff_arr, sizeof(buff_arr), f) != NULL) {
			line_count++;
		}
		fclose(f);

		f = fopen(name, "r");
		while (buff != '\n') {
			buff = (char)fgetc(f);
			if (buff == ' ') {
				space_count++;
			}
		}
		fclose(f);

		f = fopen(name, "r");
		for (int i = 0;; i++) {
			for (int j = 0; ; j++) {
				fscanf(f, "%i ", &matrix->val);
				matrix->marker = 0;
				new = (struct Matrix *)malloc(sizeof(struct Matrix));
				new->next = NULL;
				matrix->next = new;
				if (j == space_count - 1) break;
				matrix = matrix->next;
			}
			matrix->marker = 1;
			if (i == line_count - 1) break;
			matrix = matrix->next;
			fscanf(f, "\n");
		}
		matrix->next = NULL;
		fclose(f);
	}
	else {
		printf("File does not exist\n");
		fclose(f);
		return;
	}
}

struct Matrix *find_s(struct M_Count *current, struct Matrix *matrix, char *name) {
	while (matrix == NULL) {
		if (strcmp(current->name, name) == 0) {
			matrix = current->matrix;
		}
		else if (current->next == NULL) {
			printf("Wrong Matrix Name\n");
			return NULL;
		}
		else current = current->next;
	}
	return matrix;
}

struct Matrix *find_m(struct Matrix *current, int which) {
	for (int count = 0; count < which; count++) current = current->next;

	return current;
}

void helpf() {
	printf("\nEnter a letter or a word to enter new matrix\n");
	printf("To view matrices, just enter it's name in menu\n");
	printf("Here are the list of commands\n");
	printf("Sum - Sum of 2 matrices\n");
	printf("Reduce - Reduce one matrix by another\n");
	printf("Multi - Multiplication of matrices\n");
	printf("Det - Find determinant of matrix\n");
	printf("Edit - Edit matrix's values one by one by choice\n");
	printf("Save - Save matrix to a file\n");
	printf("File - Input matrix from a file\n");
	printf("Delete - Delete matrix\n");
	printf("Exit - Quit from a programm\n");
	printf("\n");
}

void keyb_enter(struct M_Count *head_2, char *proto_arg) {
	int height;
	int length;
	int val;

	printf("Enter Size of Matrix (example 10x10 for (length and height))\n");
	printf("Enter 0 for any of parameters to abort creation of matrix\n");
	scanf("%ix%i", &height, &length);
	if (height == 0 || length == 0) {
		return;
	}
	printf("Enter value for all elements of matrix\n");
	printf("Enter -1 for Custom Input\n");
	printf("Enter -2 for Random Numbers\n");
	val = checked_input();

	struct Matrix *proto_Matrix = (struct Matrix *)malloc(sizeof(struct Matrix));
	proto_Matrix->next = NULL;
	new_s(proto_Matrix, val, length, height, NULL, "");
	new_s(proto_Matrix, 0, 0, 0, head_2, proto_arg);

}

int mini_det(struct Matrix *current) {
	struct Matrix *proto_val = NULL;

	int arr_val[4] = { 0 };
	int res;

	for (int i = 0; i < 4; i++) {
		proto_val = find_m(current, i);
		arr_val[i] = proto_val->val;
	}

	res = arr_val[0] * arr_val[3] - arr_val[1] * arr_val[2];
	return res;
}

void mini_main(struct M_Count *head_2) {
	int choice;
	char proto_r[C_SIZE];
	char arg[C_SIZE];

	while (1) {
		struct M_Count *main_current = NULL;

		main_current = head_2;
		scanf("%s", proto_r);
		if (strcmp(proto_r, "Help") == 0) {
			helpf();
		}
		else if (strcmp(proto_r, "Edit") == 0) {
			edit_m(head_2);
		}
		else if (strcmp(proto_r, "Save") == 0) {
			save_m(head_2);
		}
		else if (strcmp(proto_r, "File") == 0) {
			file_m(head_2);
		}
		else if (strcmp(proto_r, "Sum") == 0) {
			arith_m(head_2, 1);
		}
		else if (strcmp(proto_r, "Reduce") == 0) {
			arith_m(head_2, -1);
		}
		else if (strcmp(proto_r, "Multi") == 0) {
			arith_m(head_2, 2);
		}
		else if (strcmp(proto_r, "Det") == 0) {
			struct Matrix *matrix = NULL;
			printf("Enter name of matrix\n");
			scanf("%s", proto_r);
			printf("%i\n", det(find_s(head_2, matrix, proto_r), 1));
		}
		// does not work yet
		else if (strcmp(proto_r, "Exit") == 0) { // exit from function
			proto_delete_m(head_2);
			return;
		}
		else if (strcmp(proto_r, "-1") == 0) {
			printf("You can't name matrix %s", proto_r);
		}
		else {
			while (1) {
				if (main_current->next == NULL) {
					keyb_enter(head_2, proto_r);
					break;
				}
				else {
					if (strcmp(main_current->name, proto_r) == 0) {
						print_Matrix(main_current->matrix);
						break;
					}
					else {
						main_current = main_current->next;
					}
				}
			}
		}
	}
}

void new_s(struct Matrix *current, int val, int l, int h, struct M_Count *current_2, char *name) {
	if (l != 0 && h != 0) {
		for (int i = 0; ; i++) {
			for (int j = 0;; j++) {
				if (val == -1) {
					printf("Enter for %ix%i: ", i + 1, j + 1);
					current->val = checked_input();
				}
				else if (val == -2) {
					current->val = rand() % 10;
				}
				else {
					current->val = val;
				}
				current->marker = 0;
				struct Matrix *new = (struct Matrix *)malloc(sizeof(struct Matrix));
				new->next = NULL;
				current->next = new;
				if (j == l - 1) {
					break;
				}
				current = current->next;
			}
			current->marker = 1;
			if (i == h - 1) {
				break;
			}
			current = current->next;
		}
		current->next = NULL;
	}
	else {
		if (current_2->next == NULL) {
			strcpy(current_2->name, name);
			current_2->matrix = current;
			struct M_Count *new_2 = (struct M_Count *)malloc(sizeof(struct M_Count));
			current_2->next = new_2;
			current_2 = current_2->next;
			current_2->next = NULL;
		}
		else {
			current_2 = current_2->next;
			new_s(current, 0, 0, 0, current_2, name);
		}
	}
}

void print_Matrix(struct Matrix *current) {
	if (current != NULL) {
		printf("%i ", current->val);
		if (current->marker == 1) {
			printf("\n");
		}
		current = current->next;
		print_Matrix(current);
	}
	return;
}

int main() {

	srand(time(NULL));

	struct M_Count *head_2 = (struct M_Count *)malloc(sizeof(struct M_Count));
	struct M_Count *main_current = (struct M_Count *)malloc(sizeof(struct M_Count)); // do not confuse with current
	head_2->next = NULL;

	printf("Enter \"Help\" to see commands\n");
	mini_main(head_2);

	return 0;
}
