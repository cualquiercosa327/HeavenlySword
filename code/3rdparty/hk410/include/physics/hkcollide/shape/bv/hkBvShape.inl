/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2006 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */

hkBvShape::hkBvShape( const hkShape* boundingVolumeShape, const hkShape* childShape ) :
	m_boundingVolumeShape(boundingVolumeShape),
	m_childShape(childShape)
{
	HK_ASSERT2(0x1f5e7ff0, childShape != HK_NULL, "Child shape cannot be NULL"); 
	HK_ASSERT2(0x2d058dd7, boundingVolumeShape != HK_NULL, "Bounding volume cannot be NULL"); 

	m_boundingVolumeShape->addReference();
}

hkBvShape::~hkBvShape()
{
	m_boundingVolumeShape->removeReference();
}

inline const hkShape* hkBvShape::getBoundingVolumeShape() const 
{ 
	return m_boundingVolumeShape; 
}

inline const hkShape* hkBvShape::getChildShape() const 
{ 
	return m_childShape.getChild(); 
}


/*
* Havok SDK - PUBLIC RELEASE, BUILD(#20060902)
*
* Confidential Information of Havok.  (C) Copyright 1999-2006 
* Telekinesys Research Limited t/a Havok. All Rights Reserved. The Havok
* Logo, and the Havok buzzsaw logo are trademarks of Havok.  Title, ownership
* rights, and intellectual property rights in the Havok software remain in
* Havok and/or its suppliers.
*
* Use of this software for evaluation purposes is subject to and indicates 
* acceptance of the End User licence Agreement for this product. A copy of 
* the license is included with this software and is also available from salesteam@havok.com.
*
*/
