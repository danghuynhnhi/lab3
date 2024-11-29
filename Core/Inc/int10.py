# Danh sách các số nguyên mà bạn muốn lưu vào file .bin
numbers = [11, 2, 33, 42, 5, 16, 7, 28, 19, 10]

# Mở file .bin ở chế độ ghi nhị phân (wb)
with open('INT10.bin', 'wb') as f:
    for number in numbers:
        # Lưu mỗi số dưới dạng 4 bytes
        f.write(number.to_bytes(4, byteorder='little'))  # Sử dụng 'little-endian' cho byte order
