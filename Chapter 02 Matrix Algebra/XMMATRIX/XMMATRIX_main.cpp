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
	//.x �� ���� ���� ������ XMStoreFloat������ �����ϱ⿡ �̷��� ��ȯ�Ͽ� ��.
	//cf. XMVECTOR�� �� ��ȣ�Ǳ⿡ ���� �޼ҵ带 �̿��ؾ���. (XMVectorGetZ ��)
	//=> XMStoreFloat�� ���� : (���� �ƴ�����) Ŭ������ ����ü�� ��� ������ �� ����(aligned) ��� / (����ó��) ���� ���� ����
	//=> �� ���ҵ��� �̿��ϱ� ���ؼ� XMStoreFloat�� ���� ������ Ÿ������ ����ϸ�, 
	//���� �����͸� �� ���� �����ϴ� XMVECTOR�� ����� �ʿ��� ���� LOAD�ؼ� ����ϰ� �ٽ� XMStoreFloat���� STORE��.
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
		cout << "DirectXMath�� �������� ����" << endl;
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