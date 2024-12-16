Collecting workspace information

Based on your codebase, which already has init system detection for OpenRC, systemd, and runit, here are the essential features your TUI init system manager should have:

1. **Service Management**
```go
// Core features for each init system
- List all available services
- Show service status (running/stopped)
- Start/Stop/Restart services
- Enable/Disable services on boot
- View service logs
```

2. **System Information**
```go
// Display info about:
- Current init system in use
- System uptime
- Running services count
- Failed services
- Resource usage
```

3. **Search & Filter**
```go
// Using github.com/sahilm/fuzzy from your go.mod:
- Fuzzy search for services
- Filter by status (running/stopped)
- Filter by enabled/disabled
```

4. **UI Components** (using Bubble Tea framework from your dependencies):
```go
// Using github.com/charmbracelet/bubbles and bubbletea:
- Interactive service list
- Status indicators
- Help menu
- Command palette
- Error messages
```

5. **Keyboard Shortcuts**
```
j/k or ↑/↓ - Navigate services
enter    - Select service
r        - Restart service
s        - Stop service
e        - Enable/disable service
/        - Search
q        - Quit
?        - Help
```

Looking at your imports, you're already set up with the right tools:
- 

github.com/charmbracelet/bubbles

 for UI components
- 

github.com/charmbracelet/bubbletea

 for TUI framework
- 

github.com/sahilm/fuzzy

 for search functionality

You can implement these features in your 

tui

 directory, using the init system detection you've already set up in 

initsys

.