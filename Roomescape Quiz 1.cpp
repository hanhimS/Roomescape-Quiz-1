#include <bangtal.h>
using namespace bangtal;

int main()
{
	// 장면 생성
	auto scene1 = Scene::create("룸1", "Roomescape images/배경-1.png");
	auto scene2 = Scene::create("룸2", "Roomescape images/배경-2.png");
	auto scene3 = Scene::create("룸3", "Roomescape images/배경-3.png");
	scene3->setLight(0.1f);
	auto scene4 = Scene::create("룸4", "Roomescape images/배경-4.png");
	auto scene5 = Scene::create("룸5", "Roomescape images/배경-5.png");

	//장면 1
	// 문1의 이벤트
	auto door1_open = false, locked_door1 = true;
	auto door1 = Object::create("Roomescape images/문-오른쪽-닫힘.png", scene1, 800, 270);
	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (locked_door1) {            // 문이 잠긴 상태
			showMessage("문이 잠겨있다");
		}
		else if (door1_open == true) {      // 문이 열린 상태
			scene2->enter();
		}
		else {                   // 문이 닫힌 상태
			door1->setImage("Roomescape images/문-오른쪽-열림.png");
			door1_open = true;
		}
		return true;
		});

	auto keypad = Object::create("Roomescape images/키패드.png", scene1, 1200, 420);
	keypad->setScale(2.5f);
	keypad->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		showKeypad("2020", door1);
		return true;
		});

	door1->setOnKeypadCallback([&](ObjectPtr object)->bool {
		locked_door1 = false;
		showMessage("끼익");
		return true;
		});

	// 장면1의 light 이벤트
	auto light1 = true;
	auto button1 = Object::create("Roomescape images/스위치.png", scene1, 600, 500);
	button1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (light1) {
			scene1->setLight(0.3f);
			showMessage("올해");
			light1 = false;
		}
		else {
			scene1->setLight(1.0f);
			light1 = true;
		}
		return true;
		});

	//화로 생성
	auto fire = Object::create("Roomescape images/화로.png", scene1, 400, 300);
	fire->setScale(0.4f);


	// 장면 2
	// 문2
	auto door2 = Object::create("Roomescape images/문-왼쪽-열림.png", scene2, 320, 270);
	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	// 문3의 이벤트
	auto door3_open = false, locked_door3 = true;
	auto door3 = Object::create("Roomescape images/문-오른쪽-닫힘.png", scene2, 900, 270);
	door3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (locked_door3) {            // 문이 잠긴 상태
			showMessage("문이 잠겨있다");
		}
		else if (door3_open == true) {      // 문이 열린 상태
			scene4->enter();
		}
		else {                   // 문이 닫힌 상태
			door3_open = true;
		}
		return true;
		});

	// 장면2의 light 이벤트
	auto light2 = true;
	auto button2 = Object::create("Roomescape images/스위치.png", scene2, 1200, 460);
	button2->setScale(2.0f);
	button2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (light2) {
			scene2->setLight(0.3f);
			locked_door3 = false;
			showMessage("철컥");
			door3->setImage("Roomescape images/문-오른쪽-열림.png");
			light2 = false;
		}
		else {
			scene2->setLight(1.0f);
			locked_door3 = true;
			door3->setImage("Roomescape images/문-오른쪽-닫힘.png");
			light2 = true;
		}
		return true;
		});
	
	//숨겨진 지하실 문
	auto door4_open = false;
	auto door4 = Object::create("Roomescape images/바닥문-닫힘.png", scene2, 520, 60);
	door4->setScale(0.5f);
	door4->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		door4->hide();
		auto door4_1 = Object::create("Roomescape images/바닥문-열림.png", scene2, 520, 60);
		door4_1->setScale(0.5f);
		door4_1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene3->enter();
			return true;
			});
		return true;
		});

	//장면2의 카펫 이벤트
	auto carpet_moved = false;
	auto carpet = Object::create("Roomescape images/카펫.png", scene2, 380, 20);
	carpet->setScale(1.8f);
	carpet->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (carpet_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_LEFT) {
				carpet->locate(scene2, 50, 20);
				carpet_moved = true;
			}
			else if (action == MouseAction::MOUSE_DRAG_RIGHT) {
				carpet->locate(scene2, 800, 20);
				carpet_moved = true;
			}
		}
		return true;
		});


	//장면 4
	//장면연결
	auto arrow2 = Object::create("Roomescape images/룸4-화살표.png", scene4, 5, 300);
	arrow2->setScale(0.5f);
	arrow2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	//촛불 생성
	auto candle = Object::create("Roomescape images/초.png", scene4, 500, 300);
	candle->setScale(0.2f);
	candle->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		candle->pick();
		return true;
		});
	fire->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (candle->isHanded()) {     
			candle->setImage("Roomescape images/촛불.png");
			scene3->setLight(1.0f);
		}
		else {
			showMessage("타닥..타닥..(다락방이..)");
		}
		return true;
		});


	//장면 3
	//장면연결
	auto arrow1 = Object::create("Roomescape images/룸3-화살표.png", scene3, 400, 620);
	arrow1->setScale(0.5f);
	arrow1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();
		return true;
		});

	//열쇠 생성
	auto key = Object::create("Roomescape images/열쇠.png", scene3, 25, 430);
	key->setScale(0.2f);
	key->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		key->pick();
		return true;
		});
	
	//사다리 생성
	auto ladder = Object::create("Roomescape images/룸3-사다리.png", scene3, 300, 100);
	ladder->setScale(0.2f);
	ladder->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		ladder->pick();
		return true;
		});
	ladder->onDrop();
	ladder->setOnDropCallback([&](ObjectPtr object)->bool {
		auto ladder_up = Object::create("Roomescape images/사다리.png", scene1, 240, 190);       //룸1에 사다리 생성하여 다락방으로 향하게 함
		ladder_up->setScale(0.3f);
		ladder->setScale(0.0f);
		ladder_up->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
			scene5->enter();
			return true;
			});
		return true;
		});


	//장면 5
	//장면연결
	auto arrow3 = Object::create("Roomescape images/룸5-화살표.png", scene5, 600, 20);
	arrow3->setScale(0.5f);
	arrow3->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	auto door5_open = false;
	auto door5 = Object::create("Roomescape images/탈출문-닫힘.png", scene5, 600, 440);
	door5->setScale(0.35f);
	door5->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (door5_open == true) {      
			endGame();
		}
		else if (key->isHanded()) {                  
			door5->setImage("Roomescape images/탈출문-열림.png");
			door5_open = true;
		}
		else {
			showMessage("잠겨있다");
		}

		return true;
		});


	// 게임을 시작
	startGame(scene1);

	return 0;

}