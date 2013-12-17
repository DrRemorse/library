#ifndef BONE_HPP
#define BONE_HPP

#include "../vector.hpp"
#include "../matrix.hpp"
#include <vector>

namespace library
{
	class Bone
	{
	public:
		Bone() {}
		Bone(const Bone& bone);
		~Bone();
		
		Bone(Bone& parent, const vec3& position, const vec3& orientation);
		Bone(const vec3& position, const vec3& orientation);
		
		void addChild(const Bone&);
		int  childCount() const
		{
			return this->children.size();
		}
		Bone& operator [] (int child) const;
		
		// returns the cumulative position & orientation
		vec3 getPosition();
		vec3 getOrientation();
		
		const mat4& getMatrix()
		{
			return getComposite();
		}
		
	private:
		const mat4& getComposite();
		void propagate();
		
		Bone* parent;
		std::vector<Bone*> children;
		
		vec3  position;
		vec3  orientation;
		
		bool   dirty;
		mat4 composite;
	};
}

#endif // BONE_HPP
