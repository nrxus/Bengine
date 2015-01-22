#pragma once

#include <vector>

namespace Bengine {
	class ParticleBatch2D;
	class SpriteBatch;

	class ParticleEngine2D {
	public:
		ParticleEngine2D();
		~ParticleEngine2D();

		void addParticleBatch(ParticleBatch2D* particleBatch);
		void draw(SpriteBatch* spriteBatch);
		void update(float deltaTime);
	private:
		std::vector<ParticleBatch2D*> m_batches;
	};
}
