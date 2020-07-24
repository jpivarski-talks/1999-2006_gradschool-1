cas2f = dp[1] + dp[2]*(x-9.46030) + dp[3]*((x-9.46030)^2 - 0.02^2);

s1 = 9.441;
s2 = 9.454;
s3 = 9.472;
s4 = 9.480;

sid = Integrate[cas2f, {x, s1, s2}] + Integrate[cas2f, {x, s3, s4}];
sig = Integrate[cas2f, {x, s2, s3}];

FortranForm[FullSimplify[sig/sid]]

sigma scale0 = 1.6164+(3915.4*dp(1)-28.128*dp(2))/(-5156.7*dp(1)+10.019*dp(2)+dp(3))

FortranForm[FullSimplify[(sig/sid /. {dp[1] -> (dp[1] + de[1])})]]

sigma scale1 = (0.018*(de(1)+dp(1))+0.0000486*dp(2)-6.5828e-6*dp(3))/(0.021*(de(1)+dp(1))-0.0000408*dp(2)-4.0724e-6*dp(3))

FortranForm[FullSimplify[(sig/sid /. {dp[2] -> (dp[2] + de[2])})]]

sigma scale2 = (0.018*dp(1)+0.0000486*(de(2)+dp(2))-6.5828e-6*dp(3))/(0.021*dp(1)-0.0000408*(de(2)+dp(2))-4.0724e-6*dp(3))

FortranForm[FullSimplify[(sig/sid /. {dp[3] -> (dp[3] + de[3])})]]

sigma scale3 = (0.018*dp(1)+0.0000486*dp(2)-6.5828e-6*(de(3)+dp(3)))/(0.021*dp(1)-0.0000408*dp(2)-4.0724e-6*(de(3)+dp(3)))

