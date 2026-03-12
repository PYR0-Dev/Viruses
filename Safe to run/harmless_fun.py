import tkinter as tk
import random
import winsound
import threading

class Ball:
    def __init__(self, canvas, x, y, diameter, color, dx, dy, app):
        self.canvas = canvas
        self.app = app
        self.id = canvas.create_oval(x, y, x + diameter, y + diameter, fill=color, outline=color)
        self.dx = dx
        self.dy = dy
        self.diameter = diameter
        self.sound_counter = 0
        
        # Bind click event to this ball
        self.canvas.tag_bind(self.id, '<Button-1>', self.on_click)
    
    def on_click(self, event):
        # Get current position
        pos = self.canvas.coords(self.id)
        x = pos[0]
        y = pos[1]
        
        # Spawn two new balls at this position
        colors = ['red', 'blue', 'green', 'yellow', 'purple', 'orange', 'pink', 
                  'cyan', 'magenta', 'lime', 'violet', 'gold', 'hotpink', 'turquoise']
        
        for _ in range(2):
            new_diameter = random.randint(25, 70)
            new_color = random.choice(colors)
            new_dx = random.choice([-15, -12, -10, -8, 8, 10, 12, 15])
            new_dy = random.choice([-15, -12, -10, -8, 8, 10, 12, 15])
            
            new_ball = Ball(self.canvas, x, y, new_diameter, new_color, new_dx, new_dy, self.app)
            self.app.balls.append(new_ball)
        
        # Play a special sound
        threading.Thread(target=lambda: winsound.Beep(1500, 100), daemon=True).start()
        
    def move(self, width, height):
        pos = self.canvas.coords(self.id)
        
        # Bounce off walls
        if pos[0] <= 0 or pos[2] >= width:
            self.dx = -self.dx
        if pos[1] <= 0 or pos[3] >= height:
            self.dy = -self.dy
        
        self.canvas.move(self.id, self.dx, self.dy)
        
        # Play sound randomly every few frames
        self.sound_counter += 1
        if self.sound_counter >= random.randint(8, 15):
            self.play_sound()
            self.sound_counter = 0
    
    def play_sound(self):
        # Play sound in separate thread to avoid blocking
        threading.Thread(target=lambda: winsound.Beep(random.randint(300, 1200), 40), daemon=True).start()

class BouncingBallsApp:
    def __init__(self):
        self.root = tk.Tk()
        self.root.title("Bouncing Balls Overlay")
        
        # Get screen dimensions
        self.width = self.root.winfo_screenwidth()
        self.height = self.root.winfo_screenheight()
        
        # Make window transparent and always on top
        self.root.attributes('-fullscreen', True)
        self.root.attributes('-topmost', True)
        self.root.attributes('-transparentcolor', 'black')
        self.root.config(bg='black')
        
        # Make window click-through (Windows only)
        self.root.overrideredirect(True)
        self.root.wm_attributes('-transparentcolor', 'black')
        
        # Create canvas with transparent background
        self.canvas = tk.Canvas(self.root, width=self.width, height=self.height, 
                                bg='black', highlightthickness=0)
        self.canvas.pack()
        
        # Create balls
        self.balls = []
        colors = ['red', 'blue', 'green', 'yellow', 'purple', 'orange', 'pink', 
                  'cyan', 'magenta', 'lime', 'violet', 'gold', 'hotpink', 'turquoise']
        
        for _ in range(35):
            x = random.randint(50, self.width - 100)
            y = random.randint(50, self.height - 100)
            diameter = random.randint(25, 70)
            color = random.choice(colors)
            dx = random.choice([-15, -12, -10, -8, 8, 10, 12, 15])
            dy = random.choice([-15, -12, -10, -8, 8, 10, 12, 15])
            
            ball = Ball(self.canvas, x, y, diameter, color, dx, dy, self)
            self.balls.append(ball)
        
        # Bind Ctrl+Shift+Esc to exit (since normal Esc won't work easily)
        self.root.bind('<Control-Shift-Escape>', lambda e: self.root.destroy())
        
        # Add small exit button in corner
        exit_btn = tk.Button(self.root, text="X", command=self.root.destroy, 
                           bg='red', fg='white', font=('Arial', 10, 'bold'))
        exit_btn.place(x=self.width - 40, y=10, width=30, height=30)
        
        # Start animation
        self.animate()
        
    def animate(self):
        for ball in self.balls:
            ball.move(self.width, self.height)
        
        self.root.after(30, self.animate)
    
    def run(self):
        self.root.mainloop()

if __name__ == "__main__":
    app = BouncingBallsApp()
    app.run()