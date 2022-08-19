// Flash Sort
#include<iostream>
using namespace std;

void InsertionSort(int* a, int n) {
	for (int i = 1; i < n; i++) {
		int x = a[i];
		int pos = i - 1;
		while (pos >= 0 && a[pos] > x) {
			a[pos + 1] = a[pos];
			pos--;
		}
		a[pos + 1] = x;
	}
}

void FlashSort(int a[], int n) {

	// Bước 1 : Tìm max và min của mảng cần sắp xếp

	int max = 0, min = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] < min) min = a[i];
		if (a[i] > max) max = a[i];
	}
	// nếu tất cả các giá trị trong mảng giống nhau thì không cần sắp xếp
	if (max == min) return;

	// Bước 2 : Khởi tạo một mảng động l có m phần tử. m là số lớp = 0.45n

	int m = floor(0.45 * n); // số lớp
	int* l = new int[m](); // mảng các lớp

	/* Bước 3 : Đếm số lượng phần tử các lớp theo quy luật,
	 phần tử a[j] sẽ thuộc lớp k = floor(((m - 1) * (a[j] - min)) / (max-min)); */

	for (int j = 0; j < n; j++) {
		// k là vị trí của lớp được phân
		int k = floor(((m - 1) * (a[j] - min)) / (max-min));
		++l[k]; // cập nhật số thành viên trong lớp k lên 1 đơn vị
	}

	// Bước 4 : Tính vị trí kết thúc của phân lớp thứ z theo công thức l[z] = l[z] + l[z-1];
	
	// cập nhật l[z] là số thứ tự cuối cùng của các lớp trong mảng 
	for (int z = 1; z < m; z++) {
		l[z] += l[z - 1];
	}
	
	/* Bước 5 : Hoán vị toàn cục. 
		Đem phần tử cần phân lớp vào vị trí thích hợp 
			-> nhấc phần tử hiện tại đang chiếm chỗ ra 
				-> tiếp tục chu trình với phần tử cần phân lớp là phần tử mới nhấc ra 
					-> lặp lại đến khi quay về vị trí ban đầu thì hoàn tất vòng lặp .*/
	int move = 0, i = 0;
	while (move < n-1) {
		// k là vị trí lớp được phân của a[i] 
		int k = floor(((m - 1) * (a[i] - min)) / (max - min));
		/* Khi i >= l[k] nghĩa là khi đó a[i] đã nằm đúng vị trí phân lớp của nó do đó ta bỏ qua và tiếp tục
		   tăng i lên để xét các phần tử tiếp theo */
		while (i >= l[k]) {
			i++;
			k = floor(((m - 1) * (a[i] - min)) / (max - min));
		}
		int flash = a[i]; // phần tử chuẩn bị đem đi phân lớp

		/* khi i = l[k] thì tương đương với việc phân lớp k đã đầy nên khi chưa đầy thì ta tiếp tục lặp.
		mỗi khi đưa 1 phần tử về đúng phân lớp của nó ta lại giảm vị trí cuối cùng của phân lớp đó xuống,
		đồng thời tăng biến đếm số lần swap lên 1 đơn vị.
		*/
		while (i != l[k]) {
			k = floor(((m - 1) * (flash - min)) / (max - min));
			--l[k];
			int hold = a[l[k]]; // phần tử nằm sai chỗ
			a[l[k]] = flash; // phân lớp k
			flash = hold; // đem phân tử nằm sai chỗ gán vào phần tử chuẩn bị đem đi phân lớp
			move++;
		}
	}

	// Bước 6 : Mảng đã chia thành các lớp nên có thứ tự gần đúng -> ta dùng Insertion Sort để hoàn tất việc sắp xếp 
	InsertionSort(a, n);
}


int main() {
	int n = 20;
	int a[20] = { 99,23,46,58,81,96,1,42,34,6,12,105,67,77,31,18,20,62,9,93 };
	FlashSort(a, n);
	for (int i = 0; i < n; i++) {
		cout << a[i] << " ";
	}
	return 0;
}