#!/usr/bin/sh

./correctionizer.pl 1 1 1 1 0 1 pass2_raw.evn pass2_everything2.evn
./correctionizer.pl 1 1 1 1 0 1 pass1_raw.evn pass1_everything2.evn
./correctionizer.pl 0 1 1 1 0 1 pass2_raw.evn pass2_missing_y1stail2.evn
./correctionizer.pl 1 0 1 1 0 1 pass2_raw.evn pass2_missing_y2stail2.evn
./correctionizer.pl 1 1 0 1 0 1 pass2_raw.evn pass2_missing_beamgas2.evn
./correctionizer.pl 1 1 1 0 0 1 pass2_raw.evn pass2_missing_twophoton2.evn
./correctionizer.pl 1 1 1 1 0 0 pass2_raw.evn pass2_missing_taus2.evn

