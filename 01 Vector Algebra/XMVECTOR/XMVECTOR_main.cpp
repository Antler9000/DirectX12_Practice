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

int main() {
	cout.setf(ios_base::boolalpha);
	cout.setf(ios_base::showpoint);

	if (!XMVerifyCPUSupport()) {
		cout << "DirectXMath를 지원하지 않음" << endl;
		return 0;
	}

	/*[1]XMVECTOR 기본 세팅
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

	/*[2]XMVECTOR 함수들
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

	/*[2]XMVECTOR 기본 연산*/
	XMVECTOR n = XMVectorSet(1.0f, 0.0f, 0.0f, 0.0f);
	XMVECTOR u = XMVectorSet(1.0f, 2.0f, 3.0f, 0.0f);
	XMVECTOR v= XMVectorSet(-2.0f, 1.0f, -3.0f, 0.0f);
	XMVECTOR w = XMVectorSet(0.707f, 0.707f, 0.0f, 0.0f);

	XMVECTOR a = u + v;				//벡터 덧셈
	
	XMVECTOR b = u - v;				//벡터 뺄셈
	
	XMVECTOR c = 10.0f * u;			//스칼라 곱셈
	
	XMVECTOR L = XMVector3Length(u);	// ||u||
	
	XMVECTOR d = XMVector3Normalize(u);	// 벡터 u 나누기 ||u||
	
	XMVECTOR s = XMVector3Dot(u, v);	//벡터 내적(1개의 값만이 나오는 내적임에도, XMVECTOR 폼 위에서 최대한 처리하기 위해 XMVECTOR의 각 모든 성분에 똑같이 결과값을 담아 반환한다.
	
	XMVECTOR e = XMVector3Cross(u, v);	//벡터 외적
	
	XMVECTOR projW;
	XMVECTOR perpW;
	XMVector3ComponentsFromNormal(&projW, &perpW, w, n);	//벡터w를 벡터 n으로 정사영한 성분만이 담긴 벡터 proj_n(w)와, 벡터w에서 벡터 n에 수직인 성분만이 담긴 벡터 perp_n(w)를 구한다

	bool equal = XMVector3Equal(projW + perpW, w);	//벡터 일치 여부 확인
	bool notEqual = XMVector3NotEqual(projW + perpW, w);

	XMVECTOR angleVec = XMVector3AngleBetweenVectors(projW, perpW);	//이것도 각도값인 스칼라 하나만을 반환하면 되지만, XMVECTOR의 각 칸에 똑같이 복붙해 반환해준다.
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