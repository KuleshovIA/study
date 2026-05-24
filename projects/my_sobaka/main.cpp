#include <cmath>
#include <iostream>
#include <windows.h>






void set_matrix (char **matrix, int size_x, int size_y, int *next_pos_x, int *next_pos_y);
void print_matrix (char **matrix, int size_x, int size_y);
void move (char **matrix, int size_x, int size_y, int *next_pos_x, int *next_pos_y);
void direction (float *x, float *y, float *cur_x, float *cur_y, int size_x, int size_y, int *pre_dir_ch, int *next_pos_x, int *next_pos_y);
void clear ();
void wait ();




int main () {
	std::setlocale (LC_ALL, "Russian");

	int size_x, size_y, angle;
	
	std::wcout << L"Введите размер поля по горизонтали:" << std::endl;
	std::cin >> size_x;
	std::wcout << L"Введите размер поля по вертикали:" << std::endl;
	std::cin >> size_y;
	std::wcout << L"Введите угол:" << std::endl;
	std::cin >> angle;
	
	char **matrix = new char *[size_y];
	for (int i = 0; i < size_x; i++) {
		matrix[i] = new char [size_x];
	}
	
	float x, y, cur_x, cur_y;
	int pre_dir_ch, next_pos_y, next_pos_x;
	x = cos (angle * M_PI / 180);
	y = sin (angle * M_PI / 180);
	cur_x = 1;
	cur_y = 1;
	pre_dir_ch = 0;
	
	
	set_matrix (matrix, size_x, size_y, &next_pos_x, &next_pos_y);
	print_matrix (matrix, size_x, size_y);
	for (int i = 0; i < 700; i++) {
		direction (&x, &y, &cur_x, &cur_y, size_x, size_y, &pre_dir_ch, &next_pos_x, &next_pos_y);
		move (matrix, size_x, size_y, &next_pos_x, &next_pos_y);
		clear ();
		print_matrix (matrix, size_x, size_y);
		wait ();
	}
	
	system ("pause");
}





void print_matrix (char **matrix, int size_x, int size_y) {
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			std::cout << *( *(matrix + i) + j);
		}
		std::cout << std::endl;
	}
}


void set_matrix (char **matrix, int size_x, int size_y, int *next_pos_x, int *next_pos_y) {
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			*( *(matrix + i) + j) = ' ';
		}
	}
	*( *(matrix + 1) + 1) = '@';
	*next_pos_x = 1;
	*next_pos_y = 1;
}


void direction (float *x, float *y, float *cur_x, float *cur_y, int size_x, int size_y, int *pre_dir_ch, int *next_pos_x, int *next_pos_y) {
	if (*next_pos_x == size_x - 1 && *next_pos_y == size_y - 1) {
		// TO DO
	}
	
	else if (*next_pos_x == size_x - 1 && *next_pos_y == 0) {
		//TO DO
	}
	
	else if (*next_pos_x == 0 && *next_pos_y == size_y - 1) {
		//TO DO
	}
	
	else if (*next_pos_x == 0 && *next_pos_y == 0) {
		//TO DO
	}
	
	else if (*next_pos_y == size_y - 1) {
		if (*pre_dir_ch != 1) {
			*y = -(*y);
			*cur_x = 1;
			*cur_y = 1;
			*pre_dir_ch = 1;
		}
		if (*x > 0) {
			if (-(*y / *x) > *cur_y / *cur_x) {
				(*next_pos_y) --;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) ++;
				(*cur_x) ++;
			}
		}
		else {
			if (*y / *x > *cur_y / *cur_x) {
				(*next_pos_y) --;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) --;
				(*cur_x) ++;
			}
		}
	}
	
	else if (*next_pos_y == 0) {
		if (*pre_dir_ch != 3) {
			*y = -(*y);
			*cur_x = 1;
			*cur_y = 1;
			*pre_dir_ch = 3;
		}
		if (*x > 0) {
			if (*y / *x > *cur_y / *cur_x) {
				(*next_pos_y) ++;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) ++;
				(*cur_x) ++;
			}
		}
		else {
			if (-(*y / *x) > *cur_y / *cur_x) {
				(*next_pos_y) ++;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) --;
				(*cur_x) ++;
			}
		}
	}
	
	else if (*next_pos_x == size_x - 1) {
		if (*pre_dir_ch != 2) {
			*x = -(*x);
			*cur_x = 1;
			*cur_y = 1;
			*pre_dir_ch = 2;
		}
		if (*y > 0) {
			if (-(*y / *x) > *cur_y / *cur_x) {
				(*next_pos_y) ++;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) --;
				(*cur_x) ++;
			}
		}
		else {
			if (*y / *x > *cur_y / *cur_x) {
				(*next_pos_y) --;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) --;
				(*cur_x) ++;
			}
		}
	}
	
	else if (*next_pos_x == 0) {
		if (*pre_dir_ch != 4) {
			*x = -(*x);
			*cur_x = 1;
			*cur_y = 1;
			*pre_dir_ch = 4;
		}
		if (*y > 0) {
			if (*y / *x > *cur_y / *cur_x) {
				(*next_pos_y) ++;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) ++;
				(*cur_x) ++;
			}
		}
		else {
			if (-(*y / *x) > *cur_y / *cur_x) {
				(*next_pos_y) --;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) ++;
				(*cur_x) ++;
			}
		}
	}
	
	else { 
		if (*x > 0 && *y > 0) {
			if (*y / *x > *cur_y / *cur_x) {
				(*next_pos_y) ++;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) ++;
				(*cur_x) ++;
			}
		}
		else if (*x < 0 && *y > 0) {
			if (-(*y / *x) > *cur_y / *cur_x) {
				(*next_pos_y) ++;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) --;
				(*cur_x) ++;
			}
		}
		else if (*x < 0 && *y < 0) {
			if (*y / *x > *cur_y / *cur_x) {
				(*next_pos_y) --;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) --;
				(*cur_x) ++;
			}
		}
		else if (*x > 0 && *y < 0) {
			if (-(*y / *x) > *cur_y / *cur_x) {
				(*next_pos_y) --;
				(*cur_y) ++;
			}
			else {
				(*next_pos_x) ++;
				(*cur_x) ++;
			}
		}
		else {
			//TO DO
		}
	}
}


void move (char **matrix, int size_x, int size_y, int *next_pos_x, int *next_pos_y) {
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			if ( *( *(matrix + i) + j) == '@' ) {
				*( *(matrix + i) + j) = '#';
			}
		}
	}
	for (int i = 0; i < size_y; i++) {
		for (int j = 0; j < size_x; j++) {
			if (i == *next_pos_y && j == *next_pos_x) {
				*( *(matrix + i) + j) = '@';
			}
		}
	}
}


void clear () {
	system ("cls");
}


void wait () {
	Sleep (10);
}
