/* 
 * 
 * Confidential Information of Telekinesys Research Limited (t/a Havok).  Not for disclosure or distribution without Havok's
 * prior written consent.This software contains code, techniques and know-how which is confidential and proprietary to Havok.
 * Level 2 and Level 3 source code contains trade secrets of Havok. Havok Software (C) Copyright 1999-2006 Telekinesys Research Limited t/a Havok. All Rights Reserved. Use of this software is subject to the terms of an end user license agreement.
 * 
 */
#ifndef HK_VISUALIZE_DISPLAY_SERIALIZE_I_STREAM_H
#define HK_VISUALIZE_DISPLAY_SERIALIZE_I_STREAM_H

#include <hkbase/stream/hkIArchive.h>
#include <hkmath/basetypes/hkGeometry.h>

// non primitive datatypes which are streamable
class hkVector4;
class hkRotation;
class hkTransform;
class hkTriangleIndices;
class hkDisplayGeometry;

/// This utility class extends the hkIArchive to provide a endian
/// safe stream interface for deserializing all of the basic data 
/// types associated with the visual debugger.
class hkDisplaySerializeIStream : public hkIArchive
{
	public:

			/// Create a hkDisplaySerializeIStream from a basic hkStreamWriter which
			/// must be readable.
		hkDisplaySerializeIStream(hkStreamReader* reader);

			/// Deserialize a hkVector4.
		void readQuadVector4(hkVector4& v);

			/// Deserialize a hkTransform.
		void readTransform(hkTransform& t);

			/// Deserialize a hkTriangleIndices.
		void readTriangle(hkGeometry::Triangle& ti);

			/// Deserialize a hkGeometry.
		void readGeometry(hkGeometry& g);

			/// Deserialize a hkDisplayGeometry.
		void readDisplayGeometry(hkDisplayGeometry*& dg);
};

#endif //  HK_VISUALIZE_DISPLAY_SERIALIZE_I_STREAM_H

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
