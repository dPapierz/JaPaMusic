#include <iostream>
#include <future>

#include <boost/asio.hpp>
#include <nanogui/nanogui.h>
#include <nanogui/layout.h>

#include "Player/Player.h"
#include "Networking/Client.h"

int main(int argc, char *argv[]) {
	boost::asio::io_context io_context;

	JaPaMusic::Player player(io_context, "localhost", "9999");
	JaPaMusic::TrackInfo info;

	std::vector<std::string> files = player.getAvailableTracks();

	nanogui::init();

	nanogui::Screen *screen = new nanogui::Screen(Eigen::Vector2i(500, 700), "JaPaMusic", false, false);

	nanogui::Window *infoWindow = new nanogui::Window(screen, "Info");
	infoWindow->setPosition(Eigen::Vector2i(250, 0));
	infoWindow->setFixedSize(Eigen::Vector2i(250, 400));
	infoWindow->setLayout(new nanogui::GroupLayout());

	nanogui::TextBox *trackInfo = new nanogui::TextBox(infoWindow);
	trackInfo->setValue("Track: ");

	nanogui::TextBox *time = new nanogui::TextBox(infoWindow);
		time->setValue("Time: 0s");

	nanogui::TextBox *rate = new nanogui::TextBox(infoWindow);
	rate->setValue("Sample rate: ");

	nanogui::Window *playerWindow = new nanogui::Window(screen, "Player");
	playerWindow->setPosition(Eigen::Vector2i(0, 400));
	playerWindow->setFixedSize(Eigen::Vector2i(500, 300));
	playerWindow->setLayout(new nanogui::GroupLayout());

	nanogui::Button *playButton = new nanogui::Button(playerWindow, "Play");
	
	playButton->setFixedSize(Eigen::Vector2i(200, 50));
	playButton->setPosition(Eigen::Vector2i(0, 0));

	playButton->setCallback([&player, &info] {
		player.start();
		while (info.currentFrame < info.frames) {
			player.play();
			info = player.getInfo();
		}
		player.end();
	});

	nanogui::Window *tracksWindow = new nanogui::Window(screen, "Tracks");
	tracksWindow->setPosition(Eigen::Vector2i(0, 0));
	tracksWindow->setFixedSize(Eigen::Vector2i(250, 400));
	tracksWindow->setLayout(new nanogui::GroupLayout());

	for (auto &file : files) {
		nanogui::Button *track = new nanogui::Button(tracksWindow, file);

		track->setCallback([&player, &info, track, trackInfo, time, rate] {
			player.getTrackInfo(track->caption());
			info = player.getInfo();

			trackInfo->setValue("Track: " + track->caption());
			time->setValue("Time: " + std::to_string(info.frames / info.samplerate) + "s");
			rate->setValue("Sample rate: " + std::to_string(info.samplerate));
		});
	}
//
	screen->setVisible(true);
	screen->performLayout();

	nanogui::mainloop();
	nanogui::shutdown();

	return 0;
}









