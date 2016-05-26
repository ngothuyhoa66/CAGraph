# Copyright (C) 2016 Nguyen Ba Ngoc

Trong các cài đặt đồ thị cơ bản thường sử dụng số nguyên (id) để ký hiệu đỉnh. Tuy nhiên trong một vài tình huống sử dụng đồ thị để phân tích các vấn đề thực tế đòi hỏi cách ký hiệu đỉnh bằng những cấu trúc dữ liệu phức tạp hơn, ví dụ như tên bến xe bus (kiểu chuỗi), tài khoản facebook (kiểu cấu trúc) v.v.

Mặt khác các giải thuật trên đồ thị như chúng ta đã biết trong khóa CAdvanced (bfs, dfs, dag, topo sort, dijikstra, v.v.) chỉ khai thác cấu trúc liên kết, mà thành phần này lại khá ổn định. Vì vậy để giải quyết bài toán khái quát hóa các giải thuật đồ thị đầu tiên chúng ta cần khái quát hóa dữ liệu đỉnh. 

Để khái quát hóa cấu trúc dữ liệu đỉnh, có thể có nhiều giải pháp khác nhau. Trong đó có thể kể đến hai giải pháp khá tự nhiên. Giải pháp 1: Chuyển đổi giữa cấu trúc dữ liệu đỉnh bất kỳ thành id và ngược lại. Giải pháp này mặc dù có thể có lợi thế về hiệu năng thực hiện các giải thuật đồ thị, tuy nhiên lại khá cồng kềnh và phức tạp trong cài đặt. Giải pháp 2 có thể sẽ đơn giản hơn trong cài đặt, và có thể là lựa chọn tối ưu vì tính đơn giản của nó: Sử dụng kiểu Jval để lưu dữ liệu đỉnh hoặc con trỏ tới những cấu trúc dữ liệu đỉnh phức tạp. Theo cách này, chúng ta cần tự định nghĩa hàm thứ tự cho hai giá trị kiểu Jval (kiểu hàm CompareFunction trong terms.h) đại diện cho hai đỉnh của đồ thị.

Còn lại cây JRB hoàn toàn phù hợp để lưu cấu trúc liên kết và trọng số cạnh đồ thị theo danh sách kề.

