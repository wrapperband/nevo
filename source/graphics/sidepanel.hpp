#pragma once

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QSlider>
#include <QGroupBox>

#include <string>

#include <world/myworld.hpp>


class SidePanel : public QWidget {
public:
	MyWorld *world;
	
	// QLabel size_label;
	QPushButton pause_button;
	
	QGroupBox delay_groupbox;
	QHBoxLayout delay_layout;
	QLabel delay_label_min, delay_label_max;
	QSlider delay_slider;
	
	QLabel delay_label;
	QLabel step_duration;
	QLabel steps_elapsed;
	
	QGroupBox stat_groupbox;
	QVBoxLayout stat_layout;
	QLabel count_label;
	QLabel age_label;
	QLabel nanc_label;
	QLabel cscore_label;
	QLabel hscore_label;
	
	QVBoxLayout layout;
	
	SidePanel(MyWorld *w) : QWidget() {
		world = w;
		
		// size_label.setText(("World size: " + std::to_string(int(world->size.x())) + "x" + std::to_string(int(world->size.y()))).c_str());
		// layout.addWidget(&size_label);
		
		pause_button.setText("Pause");
		pause_button.setCheckable(true);
		connect(&pause_button, &QPushButton::toggled, [this] (bool state){
			if(state) {
				world->paused = true;
				pause_button.setText("Continue");
			} else {
				world->paused = false;
				pause_button.setText("Pause");
			}
		});
		layout.addWidget(&pause_button);
		
		delay_groupbox.setTitle("Delay between steps");
		
		delay_slider.setFocusPolicy(Qt::NoFocus);
		delay_slider.setOrientation(Qt::Horizontal);
		delay_slider.setMinimum(1);
		delay_slider.setMaximum(40000);
		delay_slider.setSliderPosition(world->delay);
		delay_slider.setTickInterval(10000);
		delay_slider.setTickPosition(QSlider::TicksBelow);
		delay_label_min.setText("0");
		delay_label_max.setText("40 ms");
		
		delay_layout.addWidget(&delay_label_min);
		delay_layout.addWidget(&delay_slider, 1);
		delay_layout.addWidget(&delay_label_max);
		delay_groupbox.setLayout(&delay_layout);
		
		layout.addWidget(&delay_groupbox);
		
		delay_label.setText(("Delay: " + std::to_string(1e-3*world->delay) + " ms").c_str());
		connect(&delay_slider, &QSlider::sliderMoved, [this] (int p) {
			world->setDelay(p);
			delay_label.setText(("Delay: " + std::to_string(1e-3*p) + " ms").c_str());
		});
		layout.addWidget(&delay_label);
		
		layout.addWidget(&step_duration);
		layout.addWidget(&steps_elapsed);
		
		stat_groupbox.setTitle("Statistics");
		stat_layout.addWidget(&count_label);
		stat_layout.addWidget(&age_label);
		stat_layout.addWidget(&nanc_label);
		stat_layout.addWidget(&hscore_label);
		stat_layout.addWidget(&cscore_label);
		stat_groupbox.setLayout(&stat_layout);
		layout.addWidget(&stat_groupbox);
		
		layout.addStretch(1);
		
		setLayout(&layout);
	}
	
	void sync() {
		step_duration.setText(("Step duration: " + std::to_string(world->step_duration) + " ms").c_str());
		steps_elapsed.setText(("Steps elapsed: " + std::to_string(world->steps_elapsed)).c_str());
		
		// count_label.setText(("Animal count: " + std::to_string(world->anim_count)).c_str());
		// age_label.setText(("Oldest animal age: " + std::to_string(world->anim_max_age)).c_str());
		// nanc_label.setText(("Longest animal ancestry: " + std::to_string(world->anim_max_anc)).c_str());
		hscore_label.setText(("Herbivore champion score: " + std::to_string(world->hsel.max_score)).c_str());
		cscore_label.setText(("Carnivore champion score: " + std::to_string(world->csel.max_score)).c_str());
	}
};
