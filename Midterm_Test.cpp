#include <iostream>
#include <string.h>
using namespace std;

struct Car {
	int ID;
	char* Name = new char[20];
	char* Make = new char[20];
	float Price;
};

//void delete_Space(Car& item) {
//	int n_length = strlen(item.Name) + 1;
//	int m_length = strlen(item.Make) + 1;
//
//	item.Name = (char*)realloc(item.Name, n_length);
//	item.Make = (char*)realloc(item.Make, m_length);
//}

void input_Car(Car& item) {
	cout << "Nhap Id: ";
	cin >> item.ID;
	cout << "Nhap ten: ";
	cin.ignore();
	cin.getline(item.Name, 20);
	cout << "Nhap NSX: ";
	cin.getline(item.Make, 20);

	//delete_Space(item);
	cout << "Nhap gia: ";
	cin >> item.Price;

}


void input_nCar(Car*& nItem, int& n) {
	cout << "Nhap so luong xe ma ban muon nhap thong tin: ";
	cin >> n;
	nItem = new Car[n];
	for (int i = 0; i < n; i++) {
		cout << "Nhap thong tin cua xe thu " << i + 1 << ": " << endl;
		input_Car(nItem[i]);
	}
}

void output_Car(Car item) {

	cout << "Id: ";
	cout << item.ID << endl;
	cout << "Ten: ";
	cout << item.Name << endl;
	cout << "NSX: ";
	cout << item.Make << endl;
	cout << "Gia: ";
	cout << item.Price << endl;
}


void output_nCar(Car* nItem, int n) {
	if (nItem != NULL) {
		cout << "----------------------------------------------------------" << endl;
		for (int i = 0; i < n; i++) {
			cout << "Thong tin cua xe thu " << i + 1 << ": " << endl;
			output_Car(nItem[i]);
		}
		cout << "----------------------------------------------------------" << endl;
	}
	return;
}

void arr_Cop(Car* item_m, Car* item_s, int n) {
	for (int i = 0; i < n; i++) {
		item_m[i] = item_s[i];
	}
}
Car* sort_Arr(Car* nItem, int n) {
	Car* sub_Arr = new Car[n];
	arr_Cop(sub_Arr, nItem, n);
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (sub_Arr[j].Price > sub_Arr[i].Price)
				swap(sub_Arr[j].Price, sub_Arr[i].Price);
		}
	}
	return sub_Arr;
}

void list_Rank(Car* nItem, Car* list_Rank, int n, int nRank) {
	Car* Temp = sort_Arr(nItem, n);
	arr_Cop(list_Rank, Temp, nRank);
}

int list_Car_Price(Car* nItem, int n, float cmpPrice, Car*& list_price) {
	int n_list = 0;
	for (int i = 0; i < n; i++) {
		if (nItem[i].Price > cmpPrice)
			n_list++;
	}
	list_price = new Car[n_list];
	n_list = 0;
	for (int i = 0; i < n; i++) {
		if (nItem[i].Price > cmpPrice) {
			list_price[n_list] = nItem[i];
			n_list++;
		}
	}
	return n_list;
}

void write_Binary(FILE* fopen, Car* topnCar, int nCar) {
	if (fopen) {
		for (int i = 0; i < nCar; i++) {
			fwrite(&topnCar[i], sizeof(Car), 1, fopen);
		}

		fclose(fopen);
	}
	return;
}


void read_Binary(FILE* fopen, int nCar) {
	if (fopen) {
		Car trash;
		for (int i = 0; i < nCar; i++) {
			fread(&trash, sizeof(Car), 1, fopen);
			cout << "================================" << endl;
			output_Car(trash);
			cout << "================================" << endl;
		}
		fclose(fopen);
	}
	return;
}


int main()
{
	Car* arr = NULL, * listRank, * listPrice;
	int n = 0, nRank, nPrice = 0;
	input_nCar(arr, n);
	output_nCar(arr, n);
	cout << "Nhap so xe ma ban muon xuat gia cao nhat: ";
	cin >> nRank;
	listRank = new Car[nRank];
	list_Rank(arr, listRank, n, nRank);
	output_nCar(listRank, nRank);
	float cmpPrice = 0;
	cout << "Nhap gia ma ban muon tim xe co gia cao hon: ";
	cin >> cmpPrice;
	nPrice = list_Car_Price(arr, n, cmpPrice, listPrice);
	cout << "Cac xe ma ban can tim la: ";
	output_nCar(listPrice, nPrice);
//	const char *direct = "C:/Users/HOME/source/repos/Midterm_test/Midterm_test/out.bin";
//	FILE* file = fopen(direct, "w+b");
//	write_Binary(file, listPrice, nPrice);
//	file = fopen(direct, "r+b");
//	read_Binary(file, nRank);
//	fclose(file);
	return 0;
}
