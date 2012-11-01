#include "testApp.h"

//GLfloat lightOnePosition[] = {40.0, 40, 100.0, 0.0};
//GLfloat lightOneColor[] = {0.99, 0.99, 0.99, 1.0};
//
//GLfloat lightTwoPosition[] = {-40.0, 40, 100.0, 0.0};
//GLfloat lightTwoColor[] = {0.99, 0.99, 0.99, 1.0};



//--------------------------------------------------------------
void testApp::setup(){	
	ofBackground(255,255,255);
    
	ofSetVerticalSync(true);
    ofEnableLighting();
    ofEnableAlphaBlending();
    ofEnableSmoothing();
    
    // light the scene to show off why normals are important
    light.enable();
    light.setPointLight();
    light.setPosition(0,200,-150);
    
    //some model / light stuff
    glEnable (GL_DEPTH_TEST);
    //glShadeModel (GL_SMOOTH);
    
    // this sets the camera's distance from the object
	cam.setDistance(100);
    cam.setPosition(0, 30, 0);
    
    /* initialize lighting */
//    glLightfv (GL_LIGHT0, GL_POSITION, lightOnePosition);
//    glLightfv (GL_LIGHT0, GL_DIFFUSE, lightOneColor);
//    glEnable (GL_LIGHT0);
//    glLightfv (GL_LIGHT1, GL_POSITION, lightTwoPosition);
//    glLightfv (GL_LIGHT1, GL_DIFFUSE, lightTwoColor);
//    glEnable (GL_LIGHT1);
//    glEnable (GL_LIGHTING);
//    glColorMaterial (GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE );
//    glEnable (GL_COLOR_MATERIAL);
    
    //load the squirrel model - the 3ds and the texture file need to be in the same folder
    model.loadModel("zaal2.3ds", 20);
    
    //you can create as many rotations as you want
    //choose which axis you want it to effect
    //you can update these rotations later on
    model.setRotation(3, -90, 0, 0, 1);
    model.setRotation(1, -270, 1, 0, 0);
    model.setRotation(2, 180, 0, 1, 0);
    model.setScale(0.9, 0.9, 0.9);
    model.setPosition(0, 0, 0);
    
    //position = model.getPosition();
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
    ofSetColor(250,250,250);
    light.customDraw();
    
    ofSetColor(250, 0, 0);
    //ofTranslate(-position);
    //ofBox(0, 0, 0, 5);
    
//    printf("pos x: %f\n",position.x);
//    printf("pos y: %f\n",position.y);
//    printf("pos z: %f\n",position.z);

    glPushMatrix();
    glTranslatef(-64, 110, -180);
    ofDisableLighting();
    // video planes
    if(curMov) {
        ofSetColor(255, 255, 255);
        glActiveTexture(GL_TEXTURE0_ARB);
        curMov->getTextureReference().bind();
        
        glBegin(GL_QUADS);
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0,  0);
        glVertex3f( 0,  0,  0);
        glMultiTexCoord2d(GL_TEXTURE0_ARB, curMov->getWidth(), 0);
        glVertex3f( 128,  0,  0);
        glMultiTexCoord2d(GL_TEXTURE0_ARB, curMov->getWidth(), curMov->getHeight());
        glVertex3f( 128, -64,  0);
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, curMov->getHeight());
        glVertex3f( 0, -64,  0);
        glMultiTexCoord2d(GL_TEXTURE0_ARB, 0, 0);
        glVertex3f( 0,  0,  0);
        glEnd();
        
        //deactive and clean up
        glActiveTexture(GL_TEXTURE0_ARB);
        curMov->getTextureReference().unbind();
        
    } else {
        //screen 1

        ofSetColor(50, 0, 0);
        glBegin(GL_QUADS);
        glVertex3f(0,  0,  0);
        glVertex3f(128, 0,  0);
        glVertex3f(128,-64, 0);
        glVertex3f(0, -64, 0);
        glVertex3f(0,  0,  0);
        glEnd();
    }
    glPopMatrix();
    ofEnableLighting();
    cam.end();

//    ofBackground(50, 50, 50);
//    //lets tumble the world with the mouse
//    glPushMatrix();
//    
//    //draw in middle of the screen
//    glTranslatef(position.x,position.y,position.z);
//    //tumble according to mouse
//    glRotatef(-mouseY,1,0,0);
//    glRotatef(mouseX,0,1,0);
//    glTranslatef(-ofGetWidth()/2,-ofGetHeight()/2,0);
//    
//    ofSetColor(255, 255, 255, 255);
//    model.draw();
//    
//    glPopMatrix();
//    
//    ofSetHexColor(0x000000);
//    ofDrawBitmapString("fps: "+ofToString(ofGetFrameRate(), 2), 10, 15);

}

//--------------------------------------------------------------
void testApp::keyPressed(int key){
    
    
    switch (key) {
        case OF_KEY_UP:
            Tweener.addTween(position.z, position.z + 10, 2);
            //printf("tweening..\n");
            break;
        case OF_KEY_DOWN:
            Tweener.addTween(position.z, position.z - 10, 2);
            break;
        case OF_KEY_LEFT:
            Tweener.addTween(position.x, position.x + 10, 2);
            break;
        case OF_KEY_RIGHT:
            Tweener.addTween(position.x, position.x - 10, 2);
            break;
        case ',':
            Tweener.addTween(position.y, position.y + 10, 2);
            break;
        case '.':
            Tweener.addTween(position.y, position.y - 10, 2);
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
