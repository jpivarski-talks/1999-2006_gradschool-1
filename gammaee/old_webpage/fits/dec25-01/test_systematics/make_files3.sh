#!/usr/bin/sh

./correctionizer.pl 1 1 1 1 0 1 pass2_raw.evn pass2_everything3.evn
./correctionizer.pl 1 1 1 1 0 1 pass1_raw.evn pass1_everything3.evn
./correctionizer.pl 0 1 1 1 0 1 pass2_raw.evn pass2_missing_y1stail3.evn
./correctionizer.pl 1 0 1 1 0 1 pass2_raw.evn pass2_missing_y2stail3.evn
./correctionizer.pl 1 1 0 1 0 1 pass2_raw.evn pass2_missing_beamgas3.evn
./correctionizer.pl 1 1 1 0 0 1 pass2_raw.evn pass2_missing_twophoton3.evn
./correctionizer.pl 1 1 1 1 0 0 pass2_raw.evn pass2_missing_taus3.evn

