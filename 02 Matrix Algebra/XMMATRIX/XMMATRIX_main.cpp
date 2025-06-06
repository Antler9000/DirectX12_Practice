#include <windows.h>	
#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <iostream>

using namespace std;
using namespace DirectX;
using namespace DirectX::PackedVector;

ostream& XM_CALLCONV operator <<(ostream& os, FXMVECTOR v) {
	XMFLOAT3 dest;
	XMStoreFloat3(&dest, v);
	//.x 등 원소 직접 접근은 XMStoreFloat에서만 가능하기에 이렇게 변환하여 씀.
	//cf. XMVECTOR은 더 보호되기에 전용 메소드를 이용해야함. (XMVectorGetZ 등)
	//=> XMStoreFloat의 역할 : (여긴 아니지만) 클래스나 구조체의 멤버 변수일 때 정합(aligned) 명시 / (여기처럼) 원소 직접 접근
	//=> 위 역할들을 이용하기 위해서 XMStoreFloat를 저장 데이터 타입으로 사용하며, 
	//여러 데이터를 한 번에 연산하는 XMVECTOR의 기능이 필요할 때만 LOAD해서 사용하고 다시 XMStoreFloat으로 STORE함.
	os << "(" << dest.x << ", " << dest.y << ", " << dest.z << ")";
	return os;
}

ostream& XM_CALLCONV operator << (ostream& os, FXMMATRIX m) {
	for (int i = 0; i < 4; i++) {
		os << XMVectorGetX(m.r[i]) << "\t";
		os << XMVectorGetY(m.r[i]) << "\t";
		os << XMVectorGetZ(m.r[i]) << "\t";
		os << XMVectorGetW(m.r[i]) << endl;
	}
	return os;
}

int main() {
	cout.setf(ios_base::boolalpha);
	cout.setf(ios::fixed);
	cout.setf(ios::showpos);
	cout.precision(2);

	if (!XMVerifyCPUSupport()) {
		cout << "DirectXMath를 지원하지 않음" << endl;
		return 0;
	}

	XMMATRIX A(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 2.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 4.0f, 0.0f,
		1.0f, 2.0f, 3.0f, 1.0f);

	XMMATRIX B = XMMatrixIdentity();

	XMMATRIX C = A * B;

	XMMATRIX D = XMMatrixTranspose(A);

	XMVECTOR det = XMMatrixDeterminant(A);

	XMMATRIX E = XMMatrixInverse(&det, A);

	XMMATRIX F = A * E;

	cout << A << endl;
	cout << B << endl;
	cout << C << endl;
	cout << D << endl;
	cout << det << endl;
	cout << E << endl;
	cout << F << endl;

	return 0;
}