onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/clk
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/enable
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/reset
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/so_win_in
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/sel_kernel_y
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/sel_kernel_x
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/done
add wave -noupdate -radix hexadecimal /sobel_filter_vhd_tst/pix_out
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {0 ps} 0}
quietly wave cursor active 0
configure wave -namecolwidth 150
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ps
update
WaveRestoreZoom {0 ps} {128 ns}
