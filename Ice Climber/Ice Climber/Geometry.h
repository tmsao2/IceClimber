#pragma once
template<typename T>	// �^���m�肹���ɍ�邱�Ƃ��ł���

struct Vector2D {
	Vector2D() :x(0), y(0) {}
	Vector2D(T inx, T iny) : x(inx), y(iny) {}
	T x;
	T y;

	void operator+=(const Vector2D<T> &in) {
		x += in.x;
		y += in.y;
	}

	void operator-=(const Vector2D<T> &in) {
		x -= in.x;
		y -= in.y;
	}
};

///Vector2D<T>�̂��߂�+���ڰ����ް۰��
template<typename T>
Vector2D<T> operator+(Vector2D<T>& lv, Vector2D<T>&rv) {
	return Vector2D<T>(lv.x + rv.x, lv.y + rv.y);
}

//template<typename T>
//Vector2D<T> operator-(const Vector2D<T> &in) {
//	return Vector2D<T>(x - in.x, y - in.y);
//}

class Geometry
{
public:
	Geometry();
	~Geometry();
};

///�����^
typedef Vector2D<int> Vector2;
typedef Vector2 Position2;

///�����^
typedef Vector2D<float> Vector2f;
typedef Vector2f Position2f;

///�T�C�Y��\���\����
struct Size {
	Size();
	Size(int inx, int iny);
	int width;
	int height;
};

///��`��\������\����
struct Rect {
	Position2 center;
	Size size;
	Rect();
	Rect(int x, int y, int w, int h);
	Rect(Position2 &pos, Size &sz);
	const int Left()const;
	const int Right()const;
	const int Top()const;
	const int Bottom()const;
	const int Width()const { return size.width; }
	const int Height()const { return size.height; }

	///��`��`�悷��
	void Draw(unsigned int color = 0xffffffff);
	void Draw(const Vector2& offset, unsigned int color = 0xffffffff);
};


