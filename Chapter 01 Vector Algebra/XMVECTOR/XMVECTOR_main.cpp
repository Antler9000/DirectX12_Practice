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

int main() {
	cout.setf(ios_base::boolalpha);
	cout.setf(ios_base::showpoint);

	if (!XMVerifyCPUSupport()) {
		cout << "DirectXMath�� �������� ����" << endl;
		return 0;
	}

	/*[1]XMVECTOR �⺻ ����
	XMVECTOR p = XMVectorZero();
	XMVECTOR q = XMVectorSplatOne();
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v = XMVectorReplicate(-2.0f);
	XMVECTOR w = XMVectorSplatZ(u);

	cout << "p = " << p << endl;
	cout << "q = " << q << endl;
	cout << "u = " << u << endl;
	cout << "v = " << v << endl;
	cout << "w = " << w << endl;
	*/

	/*[2]XMVECTOR �Լ���
	XMVECTOR p = XMVectorSet(2.0f, 2.0f, 1.0f, 0.0f);
	XMVECTOR q = XMVectorSet(2.0f, -0.5f, 0.5f, 0.1f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 4.0f, 8.0f);
	XMVECTOR v = XMVectorSet(-2.0f, 1.0f, -3.0f, 2.5f);
	XMVECTOR w = XMVectorSet(0.0f, XM_PIDIV4, XM_PIDIV2, XM_PI);

	cout << "XMVectorAbs(v)                 = " << XMVectorAbs(v) << endl;
	cout << "XMVectorCos(w)                 = " << XMVectorCos(w) << endl;
	cout << "XMVectorLog(u)                 = " << XMVectorLog(u) << endl;
	cout << "XMVectorExp(p)                 = " << XMVectorExp(p) << endl;

	cout << "XMVectorPow(u, p)              = " << XMVectorPow(u, p) << endl;
	cout << "XMVectorSqrt(u)                = " << XMVectorSqrt(u) << endl;

	cout << "XMVectorSwizzle(u, 2, 2, 1, 3) = "
		<< XMVectorSwizzle(u, 2, 2, 1, 3) << endl;
	cout << "XMVectorSwizzle(u, 2, 1, 0, 3) = "
		<< XMVectorSwizzle(u, 2, 1, 0, 3) << endl;

	cout << "XMVectorMultiply(u, v)         = " << XMVectorMultiply(u, v) << endl;
	cout << "XMVectorSaturate(q)            = " << XMVectorSaturate(q) << endl;
	cout << "XMVectorMin(p, v               = " << XMVectorMin(p, v) << endl;
	cout << "XMVectorMax(p, v)              = " << XMVectorMax(p, v) << endl;
	*/

	/*[2]XMVECTOR �⺻ ����*/
	XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v= XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR w = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);

	XMVECTOR a = u + v;				//���� ����
	
	XMVECTOR b = u - v;				//���� ����
	
	XMVECTOR c = 10.0f * u;			//��Į�� ����
	
	XMVECTOR L = XMVector3Length(u);	// ||u||
	
	XMVECTOR d = XMVector3Normalize(u);	// ���� u ������ ||u||
	
	XMVECTOR s = XMVector3Dot(u, v);	//���� ����(1���� ������ ������ �����ӿ���, XMVECTOR �� ������ �ִ��� ó���ϱ� ���� XMVECTOR�� �� ��� ���п� �Ȱ��� ������� ��� ��ȯ�Ѵ�.
	
	XMVECTOR e = XMVector3Cross(u, v);	//���� ����
	
	XMVECTOR projW;
	XMVECTOR perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, n);	//����w�� ���� n���� ���翵�� ���и��� ��� ���� proj_n(w)��, ����w���� ���� n�� ������ ���и��� ��� ���� perp_n(w)�� ���Ѵ�

	bool equal = XMVector3Equal(projW + perpW, w);	//���� ��ġ ���� Ȯ��
	bool notEqual = XMVector3NotEqual(projW + perpW, w);

	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);	//�̰͵� �������� ��Į�� �ϳ����� ��ȯ�ϸ� ������, XMVECTOR�� �� ĭ�� �Ȱ��� ������ ��ȯ���ش�.
	float angleRadians = XMVectorGetX(angleVec);
	float angleDegrees = XMConvertToDegrees(angleRadians);

	cout << "u					= " << u << endl;
	cout << "v					= " << v << endl;
	cout << "w					= " << w << endl;
	cout << "n					= " << n << endl;
	cout << "a = u + v			= " << a << endl;
	cout << "b = u - v			= " << b << endl;
	cout << "c = 10 * u			= " << c << endl;
	cout << "d = u / ||u||			= " << d << endl;
	cout << "e = u X v			= " << e << endl;
	cout << "L = ||u||			= " << d << endl;
	cout << "s = u.v				= " << u << endl;
	cout << "projW				= " << projW << endl;
	cout << "perpW				= " << perpW << endl;
	cout << "projW + perpW == W		= " << equal << endl;
	cout << "projW + perpW != W		= " << notEqual << endl;
	cout << "angle				= " << angleDegrees << endl;

	return 0;
}