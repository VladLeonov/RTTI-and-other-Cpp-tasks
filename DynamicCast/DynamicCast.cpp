#include "pch.h"
#include "dynamicCast.h"

namespace dynamicCast {

	typedef VirtualTable::ClassesRelationship vtcr;

	map<string, list<ClassParentData>> VirtualTable::data;

	vtcr VirtualTable::getRelationship(string derivativeClassName, string baseClassName) {
		if (baseClassName.compare(derivativeClassName) == 0) {
			return {vtcr::SAME, 0};
		}
		list<ClassParentData> immediateParents = VirtualTable::data[derivativeClassName];
		vtcr relationshipBuffer = {vtcr::NOT_RELATIONSHIP , 0};
		
		for (auto i = immediateParents.begin(); i != immediateParents.end(); i++) {
			vtcr parentRelationship;
			if (baseClassName.compare(i->typeName) == 0) {
				parentRelationship = { i->isInheritedVirtually ? vtcr::VIRTUAL_PARENT : vtcr::PARENT, 0 };
			} else {
				parentRelationship = getRelationship(i->typeName, baseClassName);
			}
			
			if ((relationshipBuffer.state == vtcr::PARENT) && (parentRelationship.state != vtcr::NOT_RELATIONSHIP)) {
				relationshipBuffer.state = vtcr::AMBIGUOUS;
			}

			if ((relationshipBuffer.state == vtcr::VIRTUAL_PARENT) && 
				(parentRelationship.state != vtcr::NOT_RELATIONSHIP) && 
				(parentRelationship.state != vtcr::VIRTUAL_PARENT)) {
				relationshipBuffer.state = vtcr::AMBIGUOUS;
			}

			if (relationshipBuffer.state == vtcr::NOT_RELATIONSHIP) {
				relationshipBuffer.state = parentRelationship.state;
				if (parentRelationship.state == vtcr::PARENT) {
					relationshipBuffer.offset = parentRelationship.offset + i->offset;
				}
			}

			if (relationshipBuffer.state == vtcr::AMBIGUOUS) {
				break;
			}
		}

		return relationshipBuffer;
	}
}

	