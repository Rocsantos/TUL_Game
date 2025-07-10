#include "Collider.h"

#include <math.h>

#define DEBUG_

#ifdef DEBUG
#include "TileMap.h"
#include "Game.h"
#include <SDL2/SDL.h>
#endif // DEBUG

class Collision {
public:
	// Observação: IsColliding espera ângulos em radianos!
	// Para usar graus, forneça a sua própria implementação de Rotate,
	// ou transforme os ângulos no corpo de IsColliding.
	static inline bool IsColliding(Rect& a, Rect& b, float angleOfA, float angleOfB) {
		Vec2 A[] = { Vec2( a.x, a.y + a.h ),
						Vec2( a.x + a.w, a.y + a.h ),
						Vec2( a.x + a.w, a.y ),
						Vec2( a.x, a.y )
					};
		Vec2 B[] = { Vec2( b.x, b.y + b.h ),
						Vec2( b.x + b.w, b.y + b.h ),
						Vec2( b.x + b.w, b.y ),
						Vec2( b.x, b.y )
					};

		for (auto& v : A) {
			v = Rotate(v - a.Center(), angleOfA) + a.Center();
		}

		for (auto& v : B) {
			v = Rotate(v - b.Center(), angleOfB) + b.Center();
		}

		Vec2 axes[] = { Norm(A[0] - A[1]), Norm(A[1] - A[2]), Norm(B[0] - B[1]), Norm(B[1] - B[2]) };

		for (auto& axis : axes) {
			float P[4];

			for (int i = 0; i < 4; ++i) P[i] = Dot(A[i], axis);

			float minA = *std::min_element(P, P + 4);
			float maxA = *std::max_element(P, P + 4);

			for (int i = 0; i < 4; ++i) P[i] = Dot(B[i], axis);

			float minB = *std::min_element(P, P + 4);
			float maxB = *std::max_element(P, P + 4);

			if (maxA < minB || minA > maxB)
				return false;
		}

		return true;
	}

private:

	static inline float Mag(const Vec2& p) {
		return std::sqrt(p.x * p.x + p.y * p.y);
	}

	static inline Vec2 Norm(const Vec2& p) {
		return p * (1.f / Mag(p));
	}

	static inline float Dot(const Vec2& a, const Vec2& b) {
		return a.x * b.x + a.y * b.y;
	}

	static inline Vec2 Rotate(const Vec2& p, float angle) {
		float cs = std::cos(angle), sn = std::sin(angle);
		return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
	}
};

// Aqui estão três operadores que sua classe Vec2 deve precisar, se já não tiver. 
// Se sua classe tiver métodos para Mag, Norm, Dot e/ou Rotate, você pode substituir
// os usos desses métodos por usos dos seus, mas garanta que deem resultados corretos.

// Vec2 operator+(const Vec2& rhs) const {
//    return Vec2(x + rhs.x, y + rhs.y);
// }

// Vec2 operator-(const Vec2& rhs) const {
//    return Vec2(x - rhs.x, y - rhs.y);
// }

// Vec2 operator*(const float rhs) const {
//    return Vec2(x * rhs, y * rhs);
// }

Collider::Collider(GameObject& associated, Vec2 scale, Vec2 offset) :
	Component(associated), scale(scale), offset(offset), box(associated.box) {}

void Collider::Update(float dt)
{
	box.w *= scale.x;
	box.h *= scale.y;
	box = associated.box + (offset * associated.angleDeg);
}

void Collider::Render() {
#ifdef DEBUG
	Vec2 center( box.Center() );
	SDL_Point points[5];

	Vec2 point = (Vec2(box.x, box.y) - center).Rotate( associated.angleDeg/(180/M_1_PIf) )
					+ center - Camera::pos;
	points[0] = {(int)point.x, (int)point.y};
	points[4] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y) - center).Rotate( associated.angleDeg/(180/M_1_PIf) )
					+ center - Camera::pos;
	points[1] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x + box.w, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_1_PIf) )
					+ center - Camera::pos;
	points[2] = {(int)point.x, (int)point.y};
	
	point = (Vec2(box.x, box.y + box.h) - center).Rotate( associated.angleDeg/(180/M_1_PIf) )
					+ center - Camera::pos;
	points[3] = {(int)point.x, (int)point.y};

	SDL_SetRenderDrawColor(Game::GetInstance().GetRenderer(), 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLines(Game::GetInstance().GetRenderer(), points, 5);
#endif // DEBUG
}

bool Collider::Is(std::string type) {
	return type == "Collider";
}

void Collider::SetScale(Vec2 _scale) {
	scale = _scale;
}

void Collider::SetOffset(Vec2 _offset) {
	offset = _offset;
}

bool Collider::IsColliding (Collider* other) {
	if (other == nullptr) return false;
	return Collision::IsColliding(box, other->box, associated.angleDeg, other->associated.angleDeg);
}
