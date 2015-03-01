//
//  mesh_params.h
//  TriGen
//
//  Created by Quinn on 1/31/15.
//
//

#pragma once

struct mesh_params {
	mesh_params(float target) {
		setTargetLen(target);
	}
	
	void setTargetLen(float target) {
		targetLen = target;
		minLen = target * 4.0f/5.0f;
		maxLen = target * 4.0f/3.0f;
		minLenSq = minLen*minLen;
		maxLenSq = maxLen*maxLen;
	}
	
	float targetLen, minLen, maxLen, minLenSq, maxLenSq;
};