#!/usr/bin/sh

./correctionizer.pl 1 1 1 1 0 1 pass2_raw.evn pass2_everything4.evn
./correctionizer.pl 1 1 1 1 0 1 pass1_raw.evn pass1_everything4.evn
./correctionizer.pl 0 1 1 1 0 1 pass2_raw.evn pass2_missing_y1stail4.evn
./correctionizer.pl 1 0 1 1 0 1 pass2_raw.evn pass2_missing_y2stail4.evn
./correctionizer.pl 1 1 0 1 0 1 pass2_raw.evn pass2_missing_beamgas4.evn
./correctionizer.pl 1 1 1 0 0 1 pass2_raw.evn pass2_missing_twophoton4.evn
./correctionizer.pl 1 1 1 1 0 0 pass2_raw.evn pass2_missing_taus4.evn

echo perl differator.pl pass2_everything4.evn pass2_missing_y1stail4.evn 2 2
perl differator.pl pass2_everything4.evn pass2_missing_y1stail4.evn 2 2
echo ""

echo perl differator.pl pass2_everything4.evn pass2_missing_y2stail4.evn 2 2
perl differator.pl pass2_everything4.evn pass2_missing_y2stail4.evn 2 2
echo ""

echo perl differator.pl pass2_everything4.evn pass2_missing_beamgas4.evn 2 2
perl differator.pl pass2_everything4.evn pass2_missing_beamgas4.evn 2 2
echo ""

echo perl differator.pl pass2_everything4.evn pass2_missing_twophoton4.evn 2 2
perl differator.pl pass2_everything4.evn pass2_missing_twophoton4.evn 2 2
echo ""

echo perl differator.pl pass2_everything4.evn pass2_missing_taus4.evn 2 2
perl differator.pl pass2_everything4.evn pass2_missing_taus4.evn 2 2
echo ""

echo perl differator.pl pass2_everything4.evn pass2_everything4.evn 2 1
perl differator.pl pass2_everything4.evn pass2_everything4.evn 2 1
echo ""

echo perl differator.pl pass2_everything4.evn pass1_everything4.evn 2 2
perl differator.pl pass2_everything4.evn pass1_everything4.evn 2 2
echo ""
