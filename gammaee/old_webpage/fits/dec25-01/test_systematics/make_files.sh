#!/usr/bin/sh

./correctionizer.pl 1 1 1 1 1 1 pass2_raw.evn pass2_everything.evn
./correctionizer.pl 1 1 1 1 1 1 pass1_raw.evn pass1_everything.evn
./correctionizer.pl 0 1 1 1 1 1 pass2_raw.evn pass2_missing_y1stail.evn
./correctionizer.pl 1 0 1 1 1 1 pass2_raw.evn pass2_missing_y2stail.evn
./correctionizer.pl 1 1 0 1 1 1 pass2_raw.evn pass2_missing_beamgas.evn
./correctionizer.pl 1 1 1 0 1 1 pass2_raw.evn pass2_missing_twophoton.evn
./correctionizer.pl 1 1 1 1 0 1 pass2_raw.evn pass2_missing_mccutefficiency.evn
./correctionizer.pl 1 1 1 1 1 0 pass2_raw.evn pass2_missing_taus.evn

