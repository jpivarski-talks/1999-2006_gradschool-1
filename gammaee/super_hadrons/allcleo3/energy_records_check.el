(require 'calendar)

(defun calendar-astro-date (&optional date)
  "String of astronomical (Julian) day number after noon UTC of Gregorian DATE.
Defaults to today's date if DATE is not given."
   (ceiling
    (calendar-astro-from-absolute
     (calendar-absolute-from-gregorian
      (or date (calendar-current-date))))))

;; (defun calendar-astro-from-absolute (d)
;;   "Astronomical (Julian) day number of absolute date D."
;;   (+ d 1721424.5))

;; (defsubst calendar-absolute-from-gregorian (date)
;;   "The number of days elapsed between the Gregorian date 12/31/1 BC and DATE.
;; The Gregorian date Sunday, December 31, 1 BC is imaginary."
;;   (let ((prior-years (1- (extract-calendar-year date))))
;;     (+ (calendar-day-number date);; Days this year
;;        (* 365 prior-years);;        + Days in prior years
;;        (/ prior-years 4);;          + Julian leap years
;;        (- (/ prior-years 100));;    - century years
;;        (/ prior-years 400))));;     + Gregorian leap years

;; (defsubst calendar-day-number (date)
;;   "Return the day number within the year of the date DATE.
;; For example, (calendar-day-number '(1 1 1987)) returns the value 1,
;; while (calendar-day-number '(12 31 1980)) returns 366."
;;     (let* ((month (extract-calendar-month date))
;;            (day (extract-calendar-day date))
;;            (year (extract-calendar-year date))
;;          (day-of-year (+ day (* 31 (1- month)))))
;;       (if (> month 2)
;;           (progn
;;             (setq day-of-year (- day-of-year (/ (+ 23 (* 4 month)) 10)))
;;             (if (calendar-leap-year-p year)
;;                 (setq day-of-year (1+ day-of-year)))))
;;       day-of-year))

;; (defsubst calendar-leap-year-p (year)
;;   "Returns t if YEAR is a Gregorian leap year."
;;   (and (zerop (% year 4))
;;        (or (not (zerop (% year 100)))
;;            (zerop (% year 400)))))

(defun extract-calendar-hour (time)
  "Return the first element of a two-element list."
  (car time)
  )

(defun extract-calendar-minute (time)
  "Return the second element of a two-element list."
  (car (cdr time))
  )

(defun seconds-since-midnight (time)
  (* (+ (* (extract-calendar-hour time) 60)
	(extract-calendar-minute time)) 60)
  )

(defun cesr-timestamp-from-gregorian (date time)
  "Returns a CESR timestamp from a Gregorian date."
  (+ (* 1e6 (1- (calendar-astro-date date)))
     (floor (/ (seconds-since-midnight time) 0.0864)))
  )

(calendar-julian-date-string '(11 9 2001))
"October 27, 2001"

(- (calendar-absolute-from-gregorian '(11 9 2001))
   (calendar-absolute-from-julian '(1 1 2001)))
299


(calendar-julian-from-absolute (calendar-absolute-from-gregorian '(11 9 2001)))
(10 27 2001)





(calendar-astro-date '(11 9 2001))
2452223

(1- (calendar-astro-date '(11 9 2001)))
2452222

(* 1e6 (1- (calendar-astro-date '(11 9 2001))))
2452222000000.0


(seconds-since-midnight '())
86400

(/ (seconds-since-midnight '(24 0)) 0.0864)
1000000.0



(cesr-timestamp-from-gregorian '(11 9 2001) '(2 19))
64205967


time_stamp = 1000000 * ( julian_day - 1 ) + integer( 
seconds_since_midnight / 0.0864 )
