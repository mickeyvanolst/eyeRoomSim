#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(255,255,255);
    
	ofSetVerticalSync(true);
    
    // light the scene to show off why normals are important
    light.enable();
    light.setPointLight();
    light.setPosition(0,50,-50);
    light.setSpotlightCutOff(20);

    //some model / light stuff
    ofEnableLighting();
    glEnable(GL_NORMALIZE);
    glEnable (GL_DEPTH_TEST);
    //glShadeModel (GL_SMOOTH);
    
    // this sets the camera's distance from the object
	cam.setDistance(100);
    cam.setPosition(0, 30, 0);
    
    model.loadModel("zaal.3ds", 20);
    
    //you can create as many rotations as you want
    //choose which axis you want it to effect
    //you can update these rotations later on
    model.setRotation(3, -90, 0, 0, 1);
    model.setRotation(1, -270, 1, 0, 0);
    model.setRotation(2, 180, 0, 1, 0);
    model.setScale(0.9, 0.9, 0.9);
    model.setPosition(0, 0, 0);

    position = model.pos;

}

//--------------------------------------------------------------
void testApp::update(){
    Tweener.update();
    if(curMov) {
        curMov->idleMovie();
    }
}

//--------------------------------------------------------------
void testApp::draw(){
    ofBackground(100, 100, 100);
    
    cam.begin();
    
    ofTranslate(position);
    ofSetColor(250, 250, 250);
    model.draw();
    ofSetColor(50, 50, 50);
    light.customDraw();
    
    // left columnn 1 videoplane
    glPushMatrix();
        glTranslatef(-85, 90, -150);
        ofDisableLighting();
    
        if(curMov) {
            ofSetColor(255, 255, 255);
            glActiveTexture(GL_TEXTURE0_ARB);
            curMov->getTextureReference().bind();
        }
    
        glBegin(GL_QUADS);
        if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, 0,  0);}
        glVertex3f( 0,  0,  0);
        if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, curMov->getWidth(), 0);}
        glVertex3f( 16,  0,  0);
        if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, curMov->getWidth(), curMov->getHeight());}
        glVertex3f( 16, -64,  0);
        if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, curMov->getHeight());}
        glVertex3f( 0, -64,  0);
        if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);}
        glVertex3f( 0,  0,  0);
        glEnd();
    
        if(curMov){
            //deactive and clean up
            glActiveTexture(GL_TEXTURE0_ARB);
            curMov->getTextureReference().unbind();
        }

    glPopMatrix();
    
    // main videoplane
    glPushMatrix();
    glTranslatef(-64, 110, -180);
    ofDisableLighting();
    
    if(curMov) {
        ofSetColor(255, 255, 255);
        glActiveTexture(GL_TEXTURE0_ARB);
        curMov->getTextureReference().bind();
    }
    
    glBegin(GL_QUADS);
    if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, 0,  0);}
    glVertex3f( 0,  0,  0);
    if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, curMov->getWidth(), 0);}
    glVertex3f( 128,  0,  0);
    if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, curMov->getWidth(), curMov->getHeight());}
    glVertex3f( 128, -64,  0);
    if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, curMov->getHeight());}
    glVertex3f( 0, -64,  0);
    if(curMov){glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);}
    glVertex3f( 0,  0,  0);
    glEnd();
    
    if(curMov){
        //deactive and clean up
        glActiveTexture(GL_TEXTURE0_ARB);
        curMov->getTextureReference().unbind();
    }
    
    glPopMatrix();
    
    ofEnableLighting();
    
    cam.end();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    int goFast = 2;
    
    switch (key) {
        case OF_KEY_UP:
            Tweener.addTween(position.z, position.z + (10 * goFast), 2);
            //printf("tweening..\n");
            break;
        case OF_KEY_DOWN:
            Tweener.addTween(position.z, position.z - (10 * goFast), 2);
            break;
        case OF_KEY_LEFT:
            Tweener.addTween(position.x, position.x + (10 * goFast), 2);
            break;
        case OF_KEY_RIGHT:
            Tweener.addTween(position.x, position.x - (10 * goFast), 2);
            break;
        case ',':
            Tweener.addTween(position.y, position.y + (10 * goFast), 2);
            break;
        case '.':
            Tweener.addTween(position.y, position.y - (10 * goFast), 2);
            break;
        case 'f':
            ofToggleFullscreen();
            break;
            
        default:
            break;
    }

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){ 

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 
	if( dragInfo.files.size() > 0 ){
        
        printf("%f", dragInfo.position.x);
        
        if(curMov){
            curMov->stop();
            curMov->close();
            delete curMov;
        }
        
        curMov = new ofVideoPlayer();
        curMov->loadMovie(dragInfo.files[0]);
        curMov->play();
        
		//dragPt = info.position;
		
		//draggedImages.assign( info.files.size(), ofImage() );
		for(int k = 0; k < dragInfo.files.size(); k++){
			//draggedImages[k].loadImage(info.files[k]);
		}
	}
}
